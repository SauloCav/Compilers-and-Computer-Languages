#include "lexicalAnalyzer.h"

bool isDelimiter(char ch) {
	
	if (ch == ' ' || ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}'){
			return (true);
	}
	return (false);	
	
}

bool isComment(char* str) {
	
	return false;
	
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
		|| !strcmp(str, "%") || !strcmp(str, "++") || !strcmp(str, "--")){
			return (true);
	}	
	return (false);
	
}

bool isRelationalOperator(char* str) {
	
	if (!strcmp(str, "<") || !strcmp(str, ">") || !strcmp(str, "==") || !strcmp(str, "!=") || !strcmp(str, "!=") 
		|| !strcmp(str, ">=") || !strcmp(str, "===") || !strcmp(str, "!==")){
			return (true);
	}	
	return (false);
	
}

bool isAssignmentCommand(char* str) {
	
	if (!strcmp(str, "=") || !strcmp(str, "+=") || !strcmp(str, "-=") || !strcmp(str, "*=") || !strcmp(str, "/=") 
		|| !strcmp(str, "%=") || !strcmp(str, "**=") || !strcmp(str, "<<=") || !strcmp(str, ">>=")
		|| !strcmp(str, ">>>=") || !strcmp(str, "&=") || !strcmp(str, "^=") || !strcmp(str, "|=")){
		return (true);
	}
	return (false);
	
}

bool validIdentifier(char* str) {
	
	if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' ||
		str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9' || isDelimiter(str[0]) == true){
			return (false);
	}
	return (true);
	
}

bool isKeyword(char* str) {
	
	if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") || !strcmp(str, "break") 
		|| !strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float")
		|| !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case")
		|| !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef")
		|| !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static")
		|| !strcmp(str, "struct") || !strcmp(str, "goto") || !strcmp(str, "new") || !strcmp(str, "operator")
		|| !strcmp(str, "enum") || !strcmp(str, "enum") || !strcmp(str, "enum") || !strcmp(str, "this")
		|| !strcmp(str, "protected") || !strcmp(str, "throw") || !strcmp(str, "catch") || !strcmp(str, "class")
		|| !strcmp(str, "public") || !strcmp(str, "try") || !strcmp(str, "for") || !strcmp(str, "register")
		|| !strcmp(str, "inline") || !strcmp(str, "signed") || !strcmp(str, "default")){
			return (true);
	}	
	return (false);
	
}

bool isInteger(char* str) {
	
	int i, len = strlen(str);

	if (len == 0)
		return (false);
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
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.' ||
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
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

void parse(char* str) {
	
	int left = 0, right = 0;
	int len = strlen(str);
	int line = 1;

	printf("\n | ------- Token ------- | ------- Lexema ------- | ------- Linha ------- | \n");
	printf(" | ---------------------------------------------------------------------- | \n");
	
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
					printf("     ----- You didn't close a Comment! -----\n");
				}
	
			}
			
			else if (isFormingCharacter(subStr) == true){
				if (!strcmp(subStr, "\n")){
					line++;
				}
			}
			
			else if (isLogicalOperator(subStr) == true){
				printf(" |   <%s, LOGICAL OPERATOR>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else if (isArithmeticOperator(subStr) == true){
				printf(" |   <%s, ARITHMETIC OPERATOR>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else if (isRelationalOperator(subStr) == true){
				printf(" |   <%s, RELATIONAL OPERATOR>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else if (isAssignmentCommand(subStr) == true){
				printf(" |   <%s, ASSIGNMENT COMMAND>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else if (isScopeConstruction(subStr) == true){
				printf(" |   <%s, SCOPE CONSTRUCTOR>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else if (isBoolean(subStr) == true){
				printf(" |   <%s, DATA TYPE BOOLEAN>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else if (isString(subStr) == true){
				printf(" |   <%s, DATA TYPE STRING>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else if (isInteger(subStr) == true){
				printf(" |   <%s, DATA TYPE INTEGER>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else if (isRealNumber(subStr) == true){
				printf(" |   <%s, DATA TYPE REAL NUMBER>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else if (isKeyword(subStr) == true){
				printf(" |   <%s, KEYWORD>   |   %s   |   %d   \n", subStr, subStr, line);
			}

			else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false){
				printf(" |   <%s, VALID IDENTIFIER>   |   %s   |   %d   \n", subStr, subStr, line);
			}	

			else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false){
				printf(" |   <%s IS NOT A VALID IDENTIFIER>   |   %s   |   %d   \n", subStr, subStr, line);
			}
			
			else{
				printf(" |   <%s IS NOT A VALID LANGUAGE SYMBOL>\n");
			}
				
			left = right;
			
		}
	}
	
	printf(" | ---------------------------------------------------------------------- | \n");
	
	return;
	
}

