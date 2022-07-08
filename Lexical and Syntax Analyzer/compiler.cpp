#include "compiler.h"

struct tokenCollection{
	node** collection;
	int n;
	int k;
};

struct node{
	int line;
	char* lexer;
	char* token;
};

bool isDelimiter(char ch) {
	
	if (ch == ' ' || ch == ';' || ch == '(' || ch == ')'){
		return (true);
	}
	return (false);	
	
}

bool isScopeConstruction(char* str) {
	
	if (!strcmp(str, "begin") || !strcmp(str, "end")){
		return (true);
	}	
	return (false);
	
}

bool isLogicalOperator(char* str) {
	
	if (!strcmp(str, "&&") || !strcmp(str, "||") || !strcmp(str, "!")){
		return (true);
	}	
	return (false);
	
}

bool isArithmeticOperator(char* str) {
	
	if (!strcmp(str, "+") || !strcmp(str, "-") || !strcmp(str, "*") || !strcmp(str, "/")){
		return (true);
	}	
	return (false);
	
}

bool isRelationalOperator(char* str) {
	
	if (!strcmp(str, "<") || !strcmp(str, ">") || !strcmp(str, "==") || !strcmp(str, "<=") || !strcmp(str, ">=")){
		return (true);
	}	
	return (false);
	
}

bool validIdentifier(char* str) {
	
	if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' ||
		str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9' || isDelimiter(str[0]) == true){
			return (false);
	}
	
	if(str[(strlen(str))-1] == '@'){
		return (false);
	}
	
	if(str[0] == '@'){
		return (false);
	}
	
	if(str[0] == '#'){
		return (false);
	}
	
	return (true);
	
}

bool isKeyword(char* str) {
	
	if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "const") || !strcmp(str, "def") || !strcmp(str, "main")
		|| !strcmp(str, "int") || !strcmp(str, "float") || !strcmp(str, "string") || !strcmp(str, "bool")){
		return (true);
	}	
	return (false);
	
}

bool isInteger(char* str) {
	
	int i, len = strlen(str);

	if (len == 0){
		return (false);
	}
		
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0)){	
				return (false);
		}
	}
	return (true);
	
}

bool isRealNumber(char* str) {
	
	int i, len = strlen(str);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0)){
				return (false);
		}
			
		if (str[i] == '.'){
			hasDecimal = true;
		}
		
	}
	return (hasDecimal);
}

bool isString(char* str) {
	
	char first = str[0];
	int len = strlen(str);
	char last = str[len-1];
	
	if (('#' == first) && ('#' == last)) {
		return (true);
	}

	return (false);
	
}

bool isBoolean(char* str) {
	
	if (!strcmp(str, "false") || !strcmp(str, "true")){
		return (true);
	}	
	return (false);
	
}

char* subString(char* str, int left, int right) {
	
	int i;
	char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++){
		subStr[i - left] = str[i];
	}
	subStr[right - left + 1] = '\0';
	return (subStr);
	
}

bool isFormingCharacter(char* str) {
	
	if (!strcmp(str, "\n") || !strcmp(str, "\t") || !strcmp(str, "\v") || !strcmp(str, "\b") || !strcmp(str, "\f")){
		return (true);
	}	
	return (false);
	
}

TokenCol* tokenizer(char* str, TokenCol* col) {
	
	int left = 0, right = 0;
	int len = strlen(str);
	int line = 1;
	char* subStrLeft = (char*)malloc(sizeof(char));
	char* subStrRight = (char*)malloc(sizeof(char));

	printf("\n | ------- Token ------- | ------- Lexema ------- | ------- Linha ------- | \n");
	printf(" | ---------------------------------------------------------------------- | \n");
	
	while (right <= len && left <= right) {
		
		if (isDelimiter(str[right]) == false){
			right++;
		}
		if (isDelimiter(str[right]) == true && str[right] != ' ') {
			
			if(str[right] == ';'){
				printf(" |   DELIM_SEMICOLON   |   %c   |   %d   \n", str[right], line);
				add(col, line, ";", "DELIM_SEMICOLON");
			}
			else if(str[right] == '('){
				printf(" |   DELIM_O_PARENTHESES   |   %c   |   %d   \n", str[right], line);
				add(col, line, "(", "DELIM_O_PARENTHESES");
			}
			else if(str[right] == ')'){
				printf(" |   DELIM_C_PARENTHESES   |   %c   |   %d   \n", str[right], line);
				add(col, line, ")", "DELIM_C_PARENTHESES");
			}
			
		} 
		if (isDelimiter(str[right]) == true && left == right) {
			right++;
			left = right;
		} 
		else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) {
			
			char* subStr = subString(str, left, right - 1);
			
			if(subStr[0] == '@'){
				for(int j = left + 1; j <= strlen(str); j++){
					if(str[j] == '@'){
						right = j+1;
					}
				}
			}
			
			if (isFormingCharacter(subStr) == true){
				if (!strcmp(subStr, "\n")){
					line++;
				}
			}
			
			else if (isLogicalOperator(subStr) == true){
				
				if(!strcmp(subStr, "&&")){
					printf(" |   L_O_AND   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "L_O_AND");
				}
				else if(!strcmp(subStr, "||")){
					printf(" |   L_O_OR   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "L_O_OR");
				}
				else if(!strcmp(subStr, "!")){
					printf(" |   L_O_DENIAL   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "L_O_DENIAL");
				}

			}
			
			else if (isArithmeticOperator(subStr) == true){
				
				if(!strcmp(subStr, "+")){
					printf(" |   A_O_PLUS   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "A_O_PLUS");
				}
				else if(!strcmp(subStr, "-")){
					printf(" |   A_O_MINUS   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "A_O_MINUS");
				}
				else if(!strcmp(subStr, "/")){
					printf(" |   A_O_DIVISION   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "A_O_DIVISION");
				}
				else if(!strcmp(subStr, "/*")){
					printf(" |   A_O_MULTIPLICATION   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "A_O_MULTIPLICATION");
				}

			}
			
			else if (isRelationalOperator(subStr) == true){
				
				if(subStr[0] == '>'){
					if(subStr[1] == '='){
						printf(" |   R_O_BIGGER_EQUAL   |   %s   |   %d   \n", subStr, line);
						add(col, line, subStr, "R_O_BIGGER_EQUAL");
					}
					else{
						printf(" |   R_O_BIGGER   |   %s   |   %d   \n", subStr, line);
						add(col, line, subStr, "R_O_BIGGER");
					}
				}
				else if(subStr[0] == '<'){
					if(subStr[1] == '='){
						printf(" |   R_O_LESS_EQUAL   |   %s   |   %d   \n", subStr, line);
						add(col, line, subStr, "R_O_LESS_EQUAL");
					}
					else{
						printf(" |   R_O_LESS   |   %s   |   %d   \n", subStr, line);
						add(col, line, subStr, "R_O_LESS");
					}
				}
				else if(subStr[0] == '='){
					if(subStr[1] == '=' && subStr[2] != '='){
						printf(" |   R_O_EQUAL   |   %s   |   %d   \n", subStr, line);
						add(col, line, subStr, "R_O_EQUAL");
					}
				}

			}
			
			else if (!strcmp(subStr, "=")){
				printf(" |   ASSIGNMENT_COMMAND   |   %s   |   %d   \n", subStr, line);
				add(col, line, subStr, "ASSIGNMENT_COMMAND");
			}
			
			else if (isScopeConstruction(subStr) == true){
				
				if(!strcmp(subStr, "begin")){
					printf(" |   SCOPE_C_BEGIN   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "SCOPE_C_BEGIN");
				}
				else if(!strcmp(subStr, "end")){
					printf(" |   SCOPE_C_END   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "SCOPE_C_END");
				}
				
			}
			
			else if (isBoolean(subStr) == true){
				printf(" |   DT_BOOL   |   %s   |   %d   \n", subStr, line);
				add(col, line, subStr, "DT_BOOL");
			}
			
			else if (isString(subStr) == true){
				printf(" |   DT_STRING   |   %s   |   %d   \n", subStr, line);
				add(col, line, subStr, "DT_STRING");
			}
			
			else if (isInteger(subStr) == true){
				printf(" |   DT_INT   |   %s   |   %d   \n", subStr, line);
				add(col, line, subStr, "DT_INT");
			}
			
			else if (isRealNumber(subStr) == true){
				printf(" |   DT_FLOAT   |   %s   |   %d   \n", subStr, line);
				add(col, line, subStr, "DT_FLOAT");
			}
			
			else if (isKeyword(subStr) == true){
				
				if(!strcmp(subStr, "if")){
					printf(" |   KEYWORD_COND_IF   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "KEYWORD_COND_IF");
				}
				else if(!strcmp(subStr, "else")){
					printf(" |   KEYWORD_COND_ELSE   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "KEYWORD_COND_ELSE");
				}
				else if(!strcmp(subStr, "const")){
					printf(" |   IDENTIFIER_CONST   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "IDENTIFIER_CONST");
				}
				else if(!strcmp(subStr, "def")){
					printf(" |   KEYWORD_DEF   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "KEYWORD_DEF");
				}
				else if(!strcmp(subStr, "main")){
					printf(" |   KEYWORD_MAIN   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "KEYWORD_MAIN");
				}
				else if(!strcmp(subStr, "int")){
					printf(" |   IDENTIFIER_INT   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "IDENTIFIER_INT");
				}
				else if(!strcmp(subStr, "float")){
					printf(" |   IDENTIFIER_FLOAT   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "IDENTIFIER_FLOAT");
				}
				else if(!strcmp(subStr, "string")){
					printf(" |   IDENTIFIER_STRING   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "IDENTIFIER_STRING");
				}
				else if(!strcmp(subStr, "bool")){
					printf(" |   IDENTIFIER_BOOL   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "IDENTIFIER_BOOL");
				}
				
			}

			else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false){
				printf(" |   IDENTIFIER   |   %s   |   %d   \n", subStr, line);	
				add(col, line, subStr, "IDENTIFIER");
			}	
			
			subStrLeft = subStrRight;
			subStrRight = subString(str, left, right - 1);	
				
			left = right;
		}
	}
	
	printf(" | ---------------------------------------------------------------------- | \n");
	
	return col;
	
}

bool hasErrorLex(char* str) {
	
	int left = 0, right = 0;
	int len = strlen(str);
	int line = 1;
	
	while (right <= len && left <= right) {
		
		if (isDelimiter(str[right]) == false){
			right++;
		}
		if (isDelimiter(str[right]) == true && left == right) {
			right++;
			left = right;
		} 
		else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) {
			
			char* subStr = subString(str, left, right - 1);
			
			if(subStr[0] == '@'){
				
				int aux = 0;
	
				for(int j = left + 1; j <= strlen(str); j++){
					if(str[j] == '@'){
						right = j+1;
						aux = 1;
					}
				}
				
				if(aux == 0){
					printf("\n     ----- ERROR! You didn't close a Comment! - LINE: %d -----\n", line);
					return true;
				}
	
			}
			
			else if (isString(subStr) == false && isInteger(subStr) == false && isRealNumber(subStr) == false){
				if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false){
					printf("\n     ----- ERROR! Invalid Language Symbol - %s - LINE: %d -----\n", subStr, line);
					return true;
				}	
			}
				
			left = right;
		}
	}
	
	return false;
	
}

void parser(TokenCol* col){
		
	for(int i=0; i<col->k; i++){

		if (strcmp(col->collection[0]->lexer, "int")){
			hasErrorParse(col->collection[i]->line);
			break;
		}
		if (strcmp(col->collection[1]->lexer, "main")){
			hasErrorParse(col->collection[i]->line);
			break;
		}
		if (strcmp(col->collection[2]->lexer, "(")){
			hasErrorParse(col->collection[i]->line);
			break;
		}
		if (strcmp(col->collection[3]->lexer, ")")){
			hasErrorParse(col->collection[i]->line);
			break;
		}
		if (strcmp(col->collection[4]->lexer, "begin")){
			hasErrorParse(col->collection[i]->line);
			break;
		}
		if (!strcmp(col->collection[i]->lexer, "main") && (i > 1)){
			hasErrorParse(col->collection[i]->line);
			break;
		}

		if((i == col->k - 1) && (strcmp(col->collection[i]->lexer, "end"))){
			hasErrorParse(col->collection[i]->line);
			break;
		}

		if(i > 5){
			
			if((!strcmp(col->collection[i]->token, "L_O_AND")) || (!strcmp(col->collection[i]->token, "L_O_OR")) || (!strcmp(col->collection[i]->token, "L_O_DENIAL"))){
				logicalOperatorParser(col, i);
			}

			if ((!strcmp(col->collection[i]->token, "A_O_PLUS")) || (!strcmp(col->collection[i]->token, "A_O_MINUS")) || (!strcmp(col->collection[i]->token, "A_O_DIVISION"))){
				arithmeticOperatorParser(col, i);
			}
			else if((!strcmp(col->collection[i]->token, "A_O_MULTIPLICATION"))){
				arithmeticOperatorParser(col, i);
			}
			else if(!strcmp(col->collection[i]->token, "ASSIGNMENT_COMMAND")){
				arithmeticOperatorParser(col, i);
			}

			if((!strcmp(col->collection[i]->token, "R_O_BIGGER_EQUAL")) || (!strcmp(col->collection[i]->token, "R_O_BIGGER"))){
				relationalOperatorParser(col, i);
			}
			else if((!strcmp(col->collection[i]->token, "R_O_LESS_EQUAL")) || (!strcmp(col->collection[i]->token, "R_O_LESS"))){
				relationalOperatorParser(col, i);
			}
			else if((!strcmp(col->collection[i]->token, "R_O_EQUAL")) || (!strcmp(col->collection[i]->token, "R_O_EXACTLY_EQUAL"))){
				relationalOperatorParser(col, i);
			}
			else if((!strcmp(col->collection[i]->token, "R_O_DIFFERENT")) || (!strcmp(col->collection[i]->token, "R_O_EXACTLY_DIFFERENT"))){
				relationalOperatorParser(col, i);
			}

			if((!strcmp(col->collection[i]->token, "KEYWORD_DEF")) || (!strcmp(col->collection[i]->token, "IDENTIFIER_CONST"))){
				keywordDefConstParser(col, i);
			}

			if((!strcmp(col->collection[i]->token, "DT_BOOL")) || (!strcmp(col->collection[i]->token, "DT_STRING"))){
				dataTypeParser(col, i);
			}
			else if((!strcmp(col->collection[i]->token, "DT_INT")) || (!strcmp(col->collection[i]->token, "DT_FLOAT"))){
				dataTypeParser(col, i);
			}

			if((!strcmp(col->collection[i]->token, "IDENTIFIER_INT")) || (!strcmp(col->collection[i]->token, "IDENTIFIER_STRING"))){
				identifierTypeParser(col, i);
			}
			else if((!strcmp(col->collection[i]->token, "IDENTIFIER_BOOL")) || (!strcmp(col->collection[i]->token, "IDENTIFIER_FLOAT"))){
				identifierTypeParser(col, i);
			}

			if(!strcmp(col->collection[i]->token, "IDENTIFIER")){
				identifierParser(col, i);
			}
			
			if(!strcmp(col->collection[i]->token, "DELIM_SEMICOLON")){
				semicolonParser(col, i);
			}
			if((!strcmp(col->collection[i]->token, "DELIM_O_PARENTHESES")) || (!strcmp(col->collection[i]->token, "DELIM_C_PARENTHESES"))){
				parenthesesParser(col, i);
			}
			
			if((!strcmp(col->collection[i]->token, "SCOPE_C_BEGIN")) || (!strcmp(col->collection[i]->token, "SCOPE_C_END"))){
				scopeParser(col, i);
			}
			
			if((!strcmp(col->collection[i]->token, "KEYWORD_COND_IF")) || (!strcmp(col->collection[i]->token, "KEYWORD_COND_ELSE"))){
				conditionalParser(col, i);
			}

		}
		
	}
	
}


void logicalOperatorParser(TokenCol* col, int i) {
	printf("\n LOGICAL %s |%d| ", col->collection[i]->lexer, i);
}

void arithmeticOperatorParser(TokenCol* col, int i) {
	printf("\n ARIT %s |%d| ", col->collection[i]->lexer, i);
}

void relationalOperatorParser(TokenCol* col, int i) {
	printf("\n RELATIONAL %s |%d| ", col->collection[i]->lexer, i);
}

void keywordDefConstParser(TokenCol* col, int i) {
	printf("\n DEF_CONST %s |%d| ", col->collection[i]->lexer, i);
}

void identifierTypeParser(TokenCol* col, int i) {
	printf("\n IDENTIFIER_TYPE %s |%d| ", col->collection[i]->lexer, i);
}

void dataTypeParser(TokenCol* col, int i) {
	printf("\n DATA_TYPE %s |%d| ", col->collection[i]->lexer, i);
}

void identifierParser(TokenCol* col, int i) {
	printf("\n IDENTIFIER %s |%d| ", col->collection[i]->lexer, i);
}

void semicolonParser(TokenCol* col, int i) {
	printf("\n DOISPONTOS %s |%d| ", col->collection[i]->lexer, i);
}

void parenthesesParser(TokenCol* col, int i) {
	printf("\n PARENTHESIS %s |%d| ", col->collection[i]->lexer, i);
}

void scopeParser(TokenCol* col, int i) {
	printf("\n SCOPE %s |%d| ", col->collection[i]->lexer, i);
}

void conditionalParser(TokenCol* col, int i) {
	printf("\n COND %s |%d| ", col->collection[i]->lexer, i);
}

void hasErrorParse(int line) {
	printf("\n\n\n  Erro sintatico linha: %d ", line);
}

TokenCol* createCollection(int n){
	
	TokenCol* col = (TokenCol*) malloc(sizeof(TokenCol));
 	
 	col->n = n;
 	col->k = 0;
 	
 	col->collection = (node**) malloc(sizeof(node*) * n+1);
 	
 	return col;
	
}

int add(TokenCol* col, int line, char* lexer, char* token){
	
	if((col != NULL) && (col->k < col->n)) {
		
		Nod *no = createNode(line, lexer, token); 
		col->collection[col->k] = no;
		col->k++;
		
		return 1;
		
	}
	else{	
		return 0;
	}
	
}

Nod* createNode(int line, char* lexer, char* token){
	
	Nod *no = (Nod*) malloc(sizeof(Nod));
	
	no->line = line;
	no->lexer = lexer;
	no->token = token;
	return no;
	
}

void printCollection(TokenCol* col){
	
	int i = 0;
	
	if((col!=NULL) && (col->k>0)){
		
		printf("\nLista:\n");
		for(i=0; i<col->k; i++){
			printf("%d", i);
			printf("\n  [%d]  |  [%s]  |  [%s]  ", col->collection[i]->line, col->collection[i]->lexer, col->collection[i]->token);
		}
		
	}
	else{
		printf("\nLista Vazia!");
	}
	
}

