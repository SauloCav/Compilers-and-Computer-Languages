#include "compiler.h"

int main() {

	char str[LEN_ARRAY] = " int main () \n begin \n int x = 1 ; \n int y = 2 ; \n bool a = false ; \n if x == y : \n begin \n x = 5 ; \n end \n else : \n begin \n x = 2 ; \n end \n y = 8 \n end ";
	TokenCol* col = createCollection(100);
	
	printf("\nInput:\n");
	for (int i = 0; i < LEN_ARRAY; i ++){
		printf("%c", str[i]);
	}
	
	if((hasErrorLex(str)) == false){
		tokenizer(str, col);
	}
	
	printCollection(col);
	parser(col);

}

