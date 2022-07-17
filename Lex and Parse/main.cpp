#include "parse.h"

int main() {

	char str[LEN_ARRAY] = " int main () \n begin end ";
	TokenCol* col = createCollection(100);
	
	printf("\nInput:\n");
	for (int i = 0; i < LEN_ARRAY; i ++){
		printf("%c", str[i]);
	}
	
	if((hasErrorLex(str)) == false){
		tokenizer(str, col);
	}

	parser(col);

}

