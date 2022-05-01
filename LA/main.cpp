#include "lexicalAnalyzer.h"

int main() {

	char str[LEN_ARRAY] = " int main () \n begin \n int x = 8; \n int y = 2; \n int z = x + y; \n @this is a comment@ \n end ";
	
	printf("\nInput:\n");
	for (int i = 0; i < LEN_ARRAY; i ++){
		printf("%c", str[i]);
	}
	
	tokenizer(str);

}

