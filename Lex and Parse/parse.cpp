#include "parse.h"

void parser(TokenCol* col){
		
	for(int i=0; i<col->k; i++){

		if (strcmp(col->collection[0]->lexer, "int")){
			hasErrorParse(col->collection[i]->line, "Esperada declaração de int main()!");
			break;
		}
		if (strcmp(col->collection[1]->lexer, "main")){
			hasErrorParse(col->collection[i]->line, "Esperada declaração de int main()!");
			break;
		}
		if (strcmp(col->collection[2]->lexer, "(")){
			hasErrorParse(col->collection[i]->line, "Esperada declaração de int main()!");
			break;
		}
		if (strcmp(col->collection[3]->lexer, ")")){
			hasErrorParse(col->collection[i]->line, "Esperada declaração de int main()!");
			break;
		}
		if (strcmp(col->collection[4]->lexer, "begin")){
			hasErrorParse(col->collection[i]->line, "Esperado o construtor de escopo begin!");
			break;
		}
		if (!strcmp(col->collection[i]->lexer, "main") && (i > 1)){
			hasErrorParse(col->collection[i]->line, "main deve ser declarada apenas na funcao principal!");
			break;
		}

		if((i == col->k - 1) && (strcmp(col->collection[i]->lexer, "end"))){
			hasErrorParse(col->collection[i]->line, "O programa deve se encerrar com o fechamento de escopo end!");
			break;
		}

		if(col->collection[i]->line > 2){
			
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
				assignmentOperatorParser(col, i);
			}

			if((!strcmp(col->collection[i]->token, "R_O_BIGGER_EQUAL")) || (!strcmp(col->collection[i]->token, "R_O_BIGGER"))){
				relationalOperatorParser(col, i);
			}
			else if((!strcmp(col->collection[i]->token, "R_O_LESS_EQUAL")) || (!strcmp(col->collection[i]->token, "R_O_LESS"))){
				relationalOperatorParser(col, i);
			}
			else if((!strcmp(col->collection[i]->token, "R_O_EQUAL")) || (!strcmp(col->collection[i]->token, "R_O_DIFFERENT"))){
				relationalOperatorParser(col, i);
			}

			if(!strcmp(col->collection[i]->token, "IDENTIFIER_CONST")){
				keywordConstParser(col, i);
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
			
			if(!strcmp(col->collection[i]->token, "KEYWORD_COND_IF")){
				conditionalParser(col, i);
			}

		}
		
	}
	
}


void logicalOperatorParser(TokenCol* col, int i) {
	if(((strcmp(col->collection[i-1]->token, "DT_BOOL")) && (strcmp(col->collection[i-1]->token, "IDENTIFIER"))) ||
		((strcmp(col->collection[i+1]->token, "IDENTIFIER")) && (strcmp(col->collection[i+1]->token, "DT_BOOL")))){
			hasErrorParse(col->collection[i]->line, "Um Operador logico foi utilizado de forma incorreta!");
	}
}

void arithmeticOperatorParser(TokenCol* col, int i) {
	if(((strcmp(col->collection[i-1]->token, "DT_INT")) && (strcmp(col->collection[i-1]->token, "DT_FLOAT")) && (strcmp(col->collection[i-1]->token, "IDENTIFIER"))) ||
		((strcmp(col->collection[i+1]->token, "DT_INT")) && (strcmp(col->collection[i+1]->token, "DT_FLOAT")) && (strcmp(col->collection[i+1]->token, "IDENTIFIER")))){
			hasErrorParse(col->collection[i]->line, "Um Operador Aritmetico foi utilizado de forma incorreta!");
	}
}

void assignmentOperatorParser(TokenCol* col, int i) {
	if(((strcmp(col->collection[i-1]->token, "DT_INT")) && (strcmp(col->collection[i-1]->token, "DT_FLOAT")) && (strcmp(col->collection[i-1]->token, "IDENTIFIER")) && (strcmp(col->collection[i-1]->token, "DT_BOOL"))) ||
		((strcmp(col->collection[i+1]->token, "DT_INT")) && (strcmp(col->collection[i+1]->token, "DT_FLOAT")) && (strcmp(col->collection[i+1]->token, "IDENTIFIER")) && (strcmp(col->collection[i+1]->token, "DT_BOOL")))){
			hasErrorParse(col->collection[i]->line, "Um Operador de Atribuicao foi utilizado de forma incorreta!");
	}
}

void relationalOperatorParser(TokenCol* col, int i) {
	if(((strcmp(col->collection[i-1]->token, "DT_INT")) && (strcmp(col->collection[i-1]->token, "DT_FLOAT")) && (strcmp(col->collection[i-1]->token, "IDENTIFIER"))) ||
		((strcmp(col->collection[i+1]->token, "DT_INT")) && (strcmp(col->collection[i+1]->token, "DT_FLOAT")) && (strcmp(col->collection[i+1]->token, "IDENTIFIER")))){
			hasErrorParse(col->collection[i]->line, "Um Operador Relacional foi utilizado de forma incorreta!");
	}
}

void keywordConstParser(TokenCol* col, int i) {
	if(strcmp(col->collection[i+1]->token, "IDENTIFIER")){
		hasErrorParse(col->collection[i]->line, "Uma declaracao de variavel ou constante deve ser seguida de um identificador!");
	}
}

void identifierTypeParser(TokenCol* col, int i) {
	if(strcmp(col->collection[i+1]->token, "IDENTIFIER")){
		hasErrorParse(col->collection[i]->line, "Uma declaracao de variavel ou constante deve ser seguida de um identificador!");
	}
}

void dataTypeParser(TokenCol* col, int i) {
	
	if(!strcmp(col->collection[i]->token, "DT_BOOL")){
		if((strcmp(col->collection[i+1]->token, "L_O_AND")) && (strcmp(col->collection[i-1]->token, "L_O_AND"))){
			if((strcmp(col->collection[i+1]->token, "L_O_OR")) && (strcmp(col->collection[i-1]->token, "L_O_OR"))){
				if((strcmp(col->collection[i+1]->token, "L_O_DENIAL")) && (strcmp(col->collection[i-1]->token, "L_O_DENIAL"))){
					if(strcmp(col->collection[i-1]->token, "ASSIGNMENT_COMMAND")){
						hasErrorParse(col->collection[i]->line, "Um tipo de dado Boolean foi utilizado de forma incorreta!");
					}
				}
			}
		}
	}
	if((!strcmp(col->collection[i]->token, "DT_INT")) || (!strcmp(col->collection[i]->token, "DT_FLOAT"))) {
		if((strcmp(col->collection[i+1]->token, "A_O_PLUS")) && (strcmp(col->collection[i-1]->token, "A_O_PLUS"))){
		if((strcmp(col->collection[i+1]->token, "A_O_MINUS")) && (strcmp(col->collection[i-1]->token, "A_O_MINUS"))){
			if((strcmp(col->collection[i+1]->token, "A_O_DIVISION")) && (strcmp(col->collection[i-1]->token, "A_O_DIVISION"))){
			if((strcmp(col->collection[i+1]->token, "A_O_MULTIPLICATION")) && (strcmp(col->collection[i-1]->token, "A_O_MULTIPLICATION"))){
				if((strcmp(col->collection[i+1]->token, "R_O_BIGGER_EQUAL")) && (strcmp(col->collection[i-1]->token, "R_O_BIGGER_EQUAL"))){
				if((strcmp(col->collection[i+1]->token, "R_O_LESS_EQUAL")) && (strcmp(col->collection[i-1]->token, "R_O_LESS_EQUAL"))){
					if((strcmp(col->collection[i+1]->token, "R_O_BIGGER")) && (strcmp(col->collection[i-1]->token, "R_O_BIGGER"))){
					if((strcmp(col->collection[i+1]->token, "R_O_LESS")) && (strcmp(col->collection[i-1]->token, "R_O_LESS"))){
						if((strcmp(col->collection[i+1]->token, "R_O_EQUAL")) && (strcmp(col->collection[i-1]->token, "R_O_EQUAL"))){
						if((strcmp(col->collection[i+1]->token, "R_O_DIFFERENT")) && (strcmp(col->collection[i-1]->token, "R_O_DIFFERENT"))){
							if(strcmp(col->collection[i-1]->token, "ASSIGNMENT_COMMAND")){
								hasErrorParse(col->collection[i]->line, "Um tipo de dado Numerico foi utilizado de forma incorreta!");
							}
						}
						}
					}
					}
				}
				}
			}
			}
		}
		}
	}

}

void identifierParser(TokenCol* col, int i) {
	
	if(strcmp(col->collection[i-1]->token, "IDENTIFIER_CONST")){
	if((strcmp(col->collection[i-1]->token, "IDENTIFIER_BOOL")) && (strcmp(col->collection[i-1]->token, "IDENTIFIER_FLOAT"))){
		if((strcmp(col->collection[i-1]->token, "IDENTIFIER_INT")) && (strcmp(col->collection[i-1]->token, "IDENTIFIER_STRING"))){
		if((strcmp(col->collection[i+1]->token, "L_O_AND")) && (strcmp(col->collection[i-1]->token, "L_O_AND"))){
		if((strcmp(col->collection[i+1]->token, "L_O_OR")) && (strcmp(col->collection[i-1]->token, "L_O_OR"))){
			if((strcmp(col->collection[i+1]->token, "L_O_DENIAL")) && (strcmp(col->collection[i-1]->token, "L_O_DENIAL"))){
			if((strcmp(col->collection[i+1]->token, "A_O_PLUS")) && (strcmp(col->collection[i-1]->token, "A_O_PLUS"))){
				if((strcmp(col->collection[i+1]->token, "A_O_MINUS")) && (strcmp(col->collection[i-1]->token, "A_O_MINUS"))){
				if((strcmp(col->collection[i+1]->token, "A_O_DIVISION")) && (strcmp(col->collection[i-1]->token, "A_O_DIVISION"))){
				if((strcmp(col->collection[i+1]->token, "A_O_MULTIPLICATION")) && (strcmp(col->collection[i-1]->token, "A_O_MULTIPLICATION"))){
					if((strcmp(col->collection[i+1]->token, "R_O_BIGGER_EQUAL")) && (strcmp(col->collection[i-1]->token, "R_O_BIGGER_EQUAL"))){
					if((strcmp(col->collection[i+1]->token, "R_O_LESS_EQUAL")) && (strcmp(col->collection[i-1]->token, "R_O_LESS_EQUAL"))){
						if((strcmp(col->collection[i+1]->token, "R_O_BIGGER")) && (strcmp(col->collection[i-1]->token, "R_O_BIGGER"))){
						if((strcmp(col->collection[i+1]->token, "R_O_LESS")) && (strcmp(col->collection[i-1]->token, "R_O_LESS"))){
							if((strcmp(col->collection[i+1]->token, "R_O_EQUAL")) && (strcmp(col->collection[i-1]->token, "R_O_EQUAL"))){
							if((strcmp(col->collection[i+1]->token, "R_O_DIFFERENT")) && (strcmp(col->collection[i-1]->token, "R_O_DIFFERENT"))){
								if((strcmp(col->collection[i-1]->token, "ASSIGNMENT_COMMAND")) && (strcmp(col->collection[i+1]->token, "ASSIGNMENT_COMMAND"))){
									hasErrorParse(col->collection[i]->line, "Uso incorreto de um identificador!");
								}
							}
							}
						}
						}
					}
					}
				}
				}
				}
			}
			}
		}
		}
		}
	}
	}	
}				

void conditionalParser(TokenCol* col, int i) {
	
	int positionEnd = 0;
	
	if(strcmp(col->collection[i-1]->token, "DELIM_SEMICOLON")){
		hasErrorParse(col->collection[i-1]->line, "Ponto e virgula deve ser usado no fim de cada sentensa!");
	}
	
	if((strcmp(col->collection[i+1]->token, "DT_BOOL")) && (strcmp(col->collection[i+1]->token, "DT_STRING"))){
		if((strcmp(col->collection[i+1]->token, "DT_INT")) && (strcmp(col->collection[i+1]->token, "DT_FLOAT"))){
			if(strcmp(col->collection[i+1]->token, "IDENTIFIER")){
				hasErrorParse(col->collection[i+1]->line, "Declaracao invalida de comparacao!");
			}
		}
	}
	
	if((strcmp(col->collection[i+2]->token, "R_O_BIGGER_EQUAL")) && (strcmp(col->collection[i+2]->token, "R_O_BIGGER"))){
		if((strcmp(col->collection[i+2]->token, "R_O_LESS_EQUAL")) && (strcmp(col->collection[i+2]->token, "R_O_LESS"))){
			if((strcmp(col->collection[i+2]->token, "R_O_EQUAL")) && (strcmp(col->collection[i+2]->token, "R_O_DIFFERENT"))){
				hasErrorParse(col->collection[i+2]->line, "Declaracao invalida de comparacao!");
			}
		}
	}
	
	if((strcmp(col->collection[i+3]->token, "DT_BOOL")) && (strcmp(col->collection[i+3]->token, "DT_STRING"))){
		if((strcmp(col->collection[i+3]->token, "DT_INT")) && (strcmp(col->collection[i+3]->token, "DT_FLOAT"))){
			if(strcmp(col->collection[i+3]->token, "IDENTIFIER")){
				hasErrorParse(col->collection[i+3]->line, "Declaracao invalida de comparacao!");
			}
		}
	}
	
	if(strcmp(col->collection[i+4]->token, "DELIM_DOTS")){
		hasErrorParse(col->collection[i]->line, "Uma comparacao deve ser seguida de (:)!");
	}
	
	if(strcmp(col->collection[i+5]->token, "SCOPE_C_BEGIN")){
		hasErrorParse(col->collection[i+5]->line, "Escopo invalido!");
	}
	
	for(int j = i + 6; j < (col->k - 1); j++){
		if(!strcmp(col->collection[j]->token, "SCOPE_C_END")){
			positionEnd = j;
			break;
		}
	}
	
	if(positionEnd == 0){
		hasErrorParse(col->collection[i]->line, "Escopo invalido!");
	}
	else{
		
		if(strcmp(col->collection[positionEnd-1]->token, "DELIM_SEMICOLON")){
			hasErrorParse(col->collection[i-1]->line, "Ponto e virgula deve ser usado no fim de cada sentensa!");
		}
		
		if(!strcmp(col->collection[positionEnd+1]->token, "KEYWORD_COND_ELSE")){
			int positionEndElse = 0;
			
			if(strcmp(col->collection[positionEnd+2]->token, "DELIM_DOTS")){
				hasErrorParse(col->collection[positionEnd+2]->line, "Uma comparacao else deve ser seguida de (:)!");
			}
			for(int j = positionEnd + 3; j < (col->k - 1); j++){
				if(!strcmp(col->collection[j]->token, "SCOPE_C_END")){
					positionEndElse = j;
				}
			}
			if(positionEndElse == 0){
				hasErrorParse(col->collection[positionEnd+3]->line, "Escopo invalido!");
			}
		}
	}
	
}

void hasErrorParse(int line, char* str) {
	printf("\n\n\n  Erro sintatico linha %d: %s ", line, str);
}

