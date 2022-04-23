#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<iostream>
#include<windows.h>
#include <stdbool.h>

bool isDelimiter(char ch);
bool isOperator(char ch);
bool validIdentifier(char* str);
bool isKeyword(char* str);
bool isInteger(char* str);
bool isRealNumber(char* str);

char* subString(char* str, int left, int right);

void parse(char* str);

