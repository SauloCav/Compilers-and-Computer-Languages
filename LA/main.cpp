#include "lexicalAnalyzer.h"

int main() {

	char str[200] = "int \n a = b + \n 1c; ximira ! \t == if && false begin end for \n #pla# @ximira ninguem peixola@ 224345 4.5";

	parse(str);

}
