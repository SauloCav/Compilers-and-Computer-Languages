#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<iostream>
#include<windows.h>
#include <stdbool.h>
#include <algorithm>
#include <string>
#include <iostream>

enum TipoToken { 
  SCOPE_CONSTRUCTOR,
  KEYWORD,
  VALID_IDENTIFIER,
  NOT_VALID_IDENTIFIER,
  DELIMITER,
  OPERATOR_LOGIC,
  OPERATOR_ARITHMETIC,
  OPERATOR_RELATIONAL,
  LOGIC_EXPRESSION,
  ARITHMETIC_EXPRESSION,
  RELATIONAL_EXPRESSION,
  ASSIGNMENT_COMMAND, 
  DATA_TYPE_BOOLEAN,
  DATA_TYPE_STRING, 
  DATA_TYPE_INTEGER, 
  DATA_TYPE_REAL_NUMBER,
};


enum TipoToken { 
  KEYWORD,
  DELIMITER,
  OPERATOR_ARITHMETIC,
  OPERATOR_RELATIONAL,
  LOGIC_EXPRESSION,
  ARITHMETIC_EXPRESSION,
  RELATIONAL_EXPRESSION,
  
bool isDelimiter(char ch);
bool isOperator(char ch);
bool validIdentifier(char* str);
bool isKeyword(char* str);
bool isInteger(char* str);
bool isRealNumber(char* str);

char* subString(char* str, int left, int right);

void parse(char* str);
