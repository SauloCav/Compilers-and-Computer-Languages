#include "lexicalAnalyzer.h"

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
	
	if (!strcmp(str, "=") || !strcmp(str, "+=") || !strcmp(str, "-=") || !strcmp(str, "*=") || !strcmp(str, "/=")){
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
	
	if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "return") || !strcmp(str, "const") || !strcmp(str, "def") || !strcmp(str, "main")){
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

void isExpression(char* str, char* subStrLeft, char* subStrRight, int line) {
	
	if (isLogicalOperator(subStrRight) == true){
		
		printf("\nleft %s\n", subStrLeft);
		printf("\nright %s\n", subStrRight);

		//printf(" |   LOGICAL_OPERATOR   |   %s   |   %d   \n", str, line);
	}
			
	else if (isArithmeticOperator(subStrRight) == true){
		
		printf("\nleft %s\n", subStrLeft);
		printf("\nright %s\n", subStrRight);
		
		//printf(" |   ARITHMETIC_OPERATOR   |   %s   |   %d   \n", str, line);
	}
			
	else if (isRelationalOperator(subStrRight) == true){
		
		printf("\nleft %s\n", subStrLeft);
		printf("\nright %s\n", subStrRight);
		
		//printf(" |   RELATIONAL_OPERATOR   |   %s   |   %d   \n", str, line);
	}
	
}

void tokenizer(char* str) {
	
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
			printf(" |   DELIMITER   |   %c   |   %d   \n", str[right], line);
		} 
		if (isDelimiter(str[right]) == true && left == right) {
			right++;
			left = right;
		} 
		else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) {
			
			char* subStr = subString(str, left, right - 1);
			
			isExpression(str, subStrLeft, subStrRight, line);
			
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
				printf(" |   LOGICAL_OPERATOR   |   %s   |   %d   \n", subStr, line);
			}
			
			else if (isArithmeticOperator(subStr) == true){
				printf(" |   ARITHMETIC_OPERATOR   |   %s   |   %d   \n", subStr, line);
			}
			
			else if (isRelationalOperator(subStr) == true){
				printf(" |   RELATIONAL_OPERATOR   |   %s   |   %d   \n", subStr, line);
			}
			
			else if (isAssignmentCommand(subStr) == true){
				printf(" |   ASSIGNMENT_COMMAND   |   %s   |   %d   \n", subStr, line);
			}
			
			else if (isScopeConstruction(subStr) == true){
				printf(" |   SCOPE_CONSTRUCTOR   |   %s   |   %d   \n", subStr, line);
			}
			
			else if (isBoolean(subStr) == true){
				printf(" |   DT_BOOLEAN   |   %s   |   %d   \n", subStr, line);
			}
			
			else if (isString(subStr) == true){
				printf(" |   DT_STRING   |   %s   |   %d   \n", subStr, line);
			}
			
			else if (isInteger(subStr) == true){
				printf(" |   DDT_INTEGER   |   %s   |   %d   \n", subStr, line);
			}
			
			else if (isRealNumber(subStr) == true){
				printf(" |   DT_FLOAT   |   %s   |   %d   \n", subStr, line);
			}
			
			else if (isKeyword(subStr) == true){
				printf(" |   DT_KEYWORD   |   %s   |   %d   \n", subStr, line);
			}

			else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false){
				printf(" |   IDENTIFIER   |   %s   |   %d   \n", subStr, line);
			}	

			else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false){
				printf(" |   INVALID_IDENTIFIER   |   %s   |   %d   \n", subStr, line);
			}
			
			else{
				printf(" |   <%s IS NOT A VALID LANGUAGE SYMBOL>\n");
			}
			
			subStrLeft = subStrRight;
			subStrRight = subString(str, left, right);	
				
			left = right;
		}
	}
	
	printf(" | ---------------------------------------------------------------------- | \n");
	
	return;
	
}

