#include "lexicalAnalyzer.h"

int main() {

	char str[LEN_ARRAY] = " int main () \n begin \n int x = 1 , y = 2 , z = 3; \n @this is a comment@ \n bool a = false , b = true; a < y \n end ";
	TokenCol* col = createCollection(100);
	
	printf("\nInput:\n");
	for (int i = 0; i < LEN_ARRAY; i ++){
		printf("%c", str[i]);
	}
	
	if((hasError(str)) == false){
		tokenizer(str, col);
	}
	
	printCollection(col);

}

