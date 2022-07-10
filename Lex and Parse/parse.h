#include "lex.h"

using namespace std;

void parser(TokenCol* col);	
void logicalOperatorParser(TokenCol* col, int i);
void arithmeticOperatorParser(TokenCol* col, int i);
void relationalOperatorParser(TokenCol* col, int i);
void assignmentOperatorParser(TokenCol* col, int i);
void keywordConstParser(TokenCol* col, int i);
void identifierTypeParser(TokenCol* col, int i);
void dataTypeParser(TokenCol* col, int i);
void identifierParser(TokenCol* col, int i);
void semicolonParser(TokenCol* col, int i);
void scopeParser(TokenCol* col, int i);
void conditionalParser(TokenCol* col, int i);
void hasErrorParse(int line, char* str);

