#include "lexicalAnalyzer.h"

int main() {

	char str[LEN_ARRAY] = " int main ()  begin end ";
	TokenCol* col = createCollection(100);
	
	printf("\nInput:\n");
	for (int i = 0; i < LEN_ARRAY; i ++){
		printf("%c", str[i]);
	}
	
	if((hasError(str)) == false){
		tokenizer(str, col);
	}

}

