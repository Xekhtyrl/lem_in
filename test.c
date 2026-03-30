#include <stdio.h>

char *f(char str[]){
	for (int i = 0; str[i]; i++)
		str[i] += 1;
	return str;
}

int test(char* str) {
	int i = 0;
	for (i; str[i]; i++)
		str[i] += 1;
	return i;
}

void ff(char *str, char *(fn)(char str[]), int (fn2)(char str[])){
	printf("%s (%i)\n", fn(str), fn2(str));
}

int main() {
	char s[9] = "oooopooo";
	ff(s, f, test);
}


[0, 1, 0, 0, 0, 0, 0, 0] 0
[0, 0, 0, 0, 1, 0, 0, 0] 1
[1, 0, 0, 1, 0, 0, 0, 0] 1
[0, 0, 0, 0, 0, 0, 1, 0] 2
[0, 0, 0, 0, 0, 1, 0, 0] 2
[0, 0, 1, 0, 0, 0, 0, 0] 2
[0, 0, 0, 0, 0, 0, 0, 1] 3
[0, 0, 0, 0, 1, 0, 0, 0] 3

0 2
2 5
5 7