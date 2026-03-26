#include <stdio.h>

void f(char str[]){
	str = "";
}

int main() {
	char s[9] = "oooopooo";
	printf("%s\n",s );
	f(s);
	printf("%s\n",s );
}