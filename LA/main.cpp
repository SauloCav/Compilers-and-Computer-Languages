#include "lexicalAnalyzer.h"

int main() {

	char str[LEN_ARRAY] = " int main () \n begin \n int x = 1, y = 2, z = 3; \n bool a = false, b = true; \n end ";
	
	printf("\nInput:\n");
	for (int i = 0; i < LEN_ARRAY; i ++){
		printf("%c", str[i]);
	}
	
	tokenizer(str);

}

