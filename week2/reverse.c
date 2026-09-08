#include <stdio.h>

void my_strrev(char* p1) {
	char* p2 = p1;
	char c;
	while(*p2 != '\0') {
		++p2;
	}
	--p2;
	while(p2 > p1) {
		c = *p1;
		*p1 = *p2;
		*p2 = c;
		--p2;
		++p1;
	}
}

int main() {
	char str[255] = "Donald Trump";
	my_strrev(str);
	printf("%s\n", str);
	return 0;
}
