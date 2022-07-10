#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#include<algorithm>
#include<iostream>

#define LEN_ARRAY 800

typedef struct node Nod;

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

typedef struct tokenCollection TokenCol;

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
bool hasErrorLex(char* str);

char* subString(char* str, int left, int right);

void isExpression(char* str, char* subStrLeft, char* subStrRight, int line);

TokenCol* tokenizer(char* str, TokenCol* col);
TokenCol* createCollection(int n);
Nod*  createNode(int line, char* lexer, char* token);

int add(TokenCol* col, int line, char* lexer, char* token);

void printCollection(TokenCol* col);

