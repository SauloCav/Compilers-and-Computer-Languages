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

enum token { 
  OPERATOR_LOGIC, 
  OPERATOR_ARITHMETIC, 
  OPERATOR_RELATIONAL, 
  ASSIGNMENT_COMMAND, 
  SCOPE_CONSTRUCTOR, 
  DATA_TYPE_BOOLEAN,
  DATA_TYPE_STRING, 
  DATA_TYPE_INTEGER, 
  DATA_TYPE_REAL_NUMBER,
  KEYWORD,
  VALID_TERMINAL,
  NOT_VALID_TERMINAL
};

bool isDelimiter(char ch);
bool isOperator(char ch);
bool validIdentifier(char* str);
bool isKeyword(char* str);
bool isInteger(char* str);
bool isRealNumber(char* str);

char* subString(char* str, int left, int right);

void parse(char* str);

