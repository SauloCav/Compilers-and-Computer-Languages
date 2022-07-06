#include "lexicalAnalyzer.h"

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
	
	if (ch == ' ' || ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}'){
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
	
	if (!strcmp(str, "+") || !strcmp(str, "-") || !strcmp(str, "*") || !strcmp(str, "/") || !strcmp(str, "**") 
		|| !strcmp(str, "%")){
			return (true);
	}	
	return (false);
	
}

bool isRelationalOperator(char* str) {
	
	if (!strcmp(str, "<") || !strcmp(str, ">") || !strcmp(str, "==") || !strcmp(str, "<=") || !strcmp(str, "!=") 
		|| !strcmp(str, ">=") || !strcmp(str, "===") || !strcmp(str, "!==")){
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

void isExpression(TokenCol* col, char* str, char* subStrLeft, char* subStrRight, int line) {
	
	char* lex;
	
	if (isLogicalOperator(subStrRight) == true){
		if (validIdentifier(subStrLeft) == true && (validIdentifier(str) == true)){
			printf(" |   LOGICAL_EXPRESSION   |   %s %s %s   |   %d   \n", subStrLeft, subStrRight, str, line);
		}
	}
	else if (isArithmeticOperator(subStrRight) == true){
		if (validIdentifier(subStrLeft) == true && (validIdentifier(str) == true)){
			printf(" |   ARITHMETIC_EXPRESSION   |   %s %s %s   |   %d   \n", subStrLeft, subStrRight, str, line);
		}
	}
	else if (isRelationalOperator(subStrRight) == true){
		if (validIdentifier(subStrLeft) == true && (validIdentifier(str) == true)){
			printf(" |   RELATIONAL_EXPRESSION   |   %s %s %s   |   %d   \n", subStrLeft, subStrRight, str, line);
		}
	}	
	
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
			
			if(str[right] == ','){
				printf(" |   DELIM_COMMA   |   %c   |   %d   \n", str[right], line);
				add(col, line, ",", "DELIM_COMMA");
			}
			else if(str[right] == ';'){
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
			else if(str[right] == '['){
				printf(" |   DELIM_O_SQ_BRACKET   |   %c   |   %d   \n", str[right], line);
				add(col, line, "[", "DELIM_O_SQ_BRACKET");
			}
			else if(str[right] == ']'){
				printf(" |   DELIM_C_SQ_BRACKET   |   %c   |   %d   \n", str[right], line);
				add(col, line, "]", "DELIM_C_SQ_BRACKET");
			}
			else if(str[right] == '{'){
				printf(" |   DELIM_O_BRACKET   |   %c   |   %d   \n", str[right], line);
				add(col, line, "{", "DELIM_O_BRACKET");
			}
			else if(str[right] == '}'){
				printf(" |   DELIM_C_BRACKET   |   %c   |   %d   \n", str[right], line);
				add(col, line, "}", "DELIM_C_BRACKET");
			}
			
		} 
		if (isDelimiter(str[right]) == true && left == right) {
			right++;
			left = right;
		} 
		else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) {
			
			char* subStr = subString(str, left, right - 1);
			
			isExpression(col, subStr, subStrLeft, subStrRight, line);
			
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
				else if(!strcmp(subStr, "%")){
					printf(" |   A_O_MOD   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "A_O_MOD");
				}
				else if(!strcmp(subStr, "/*")){
					printf(" |   A_O_MULTIPLICATION   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "A_O_MULTIPLICATION");
				}
				else if(!strcmp(subStr, "**")){
					printf(" |   A_O_POW   |   %s   |   %d   \n", subStr, line);
					add(col, line, subStr, "A_O_POW");
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
					else if(subStr[1] == '=' && subStr[2] == '='){
						printf(" |   R_O_EXACTLY_EQUAL   |   %s   |   %d   \n", subStr, line);
						add(col, line, subStr, "R_O_EXACTLY_EQUAL");
					}
				}
				else if(subStr[0] == '!'){
					if(subStr[1] == '=' && subStr[2] != '='){
						printf(" |   R_O_DIFFERENT   |   %s   |   %d   \n", subStr, line);
						add(col, line, subStr, "R_O_DIFFERENT");
					}
					else if(subStr[1] == '=' && subStr[2] == '='){
						printf(" |   R_O_EXACTLY_DIFFERENT   |   %s   |   %d   \n", subStr, line);
						add(col, line, subStr, "R_O_EXACTLY_DIFFERENT");
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

bool hasError(char* str) {
	
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
			printf("\n  [%d]  |  [%s]  |  [%s]  ", col->collection[i]->line, col->collection[i]->lexer, col->collection[i]->token);
		}
		
	}
	else{
		printf("\nLista Vazia!");
	}
	
}

