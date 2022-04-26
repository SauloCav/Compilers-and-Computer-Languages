#include "lexicalAnalyzer.h"

int main() {

	char str[800] = "begin end \n && || ! \n + - * / ** % ++ -- \n < > == != != >= === !== \n = += -= *= /= %= **= <<= >>= >>>= &= ^= |= \n if else while do break continue int double float return char case sizeof long short typedef switch unsigned void static struct goto new operator enum enum enum this protected throw catch class public try for register inline signed default \n 123 542 \n 45.09 87.4 \n #ximira# #peixola# \n false true ";

	parse(str);

}
