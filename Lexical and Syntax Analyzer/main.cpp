#include "compiler.h"

int main() {

	char str[LEN_ARRAY] = " int main () \n begin \n int x = 1; \n int y = 3; \n int z = 6; \n @this is a comment@ \n bool a = false; b = true; x < y \n end ";
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

