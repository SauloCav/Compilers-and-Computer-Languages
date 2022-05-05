#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#include<algorithm>
#include<iostream>

using namespace std;

#define LEN_ARRAY 800

typedef struct tokenCollection TokenCol;
typedef struct node Nod;

bool isDelimiter(char ch);
bool isScopeConstruction(char* str);
bool isLogicalOperator(char* str);
bool isArithmeticOperator(char* str);
bool isRelationalOperator(char* str);
bool validIdentifier(char* str);
bool isKeyword(char* str);
bool isInteger(char* str);
bool isRealNumber(char* str);
bool isString(char* str);
bool isBoolean(char* str);
bool isFormingCharacter(char* str);
bool hasError(char* str);

char* subString(char* str, int left, int right);

void isExpression(char* str, char* subStrLeft, char* subStrRight, int line);
TokenCol* tokenizer(char* str, TokenCol* col);
void printMap();

Nod*  createNode(int line, char* lexer, char* token);

TokenCol* createCollection(int n);

int add(TokenCol* col, int line, char* lexer, char* token);

void printCollection(TokenCol* col);

