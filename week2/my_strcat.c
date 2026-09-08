#include <stdio.h>
char* my_strcat(char* dst, const char* src) {
	char* p = dst;
	const char* p2 = src;
	while(*p != '\0') {
		++p;
	}
	while(*p2 != '\0') {
		*p = *p2;
		++p2;
		++p;
	}
	*p='\0';
	return p;
}

int main() {
	char dst[8] = "Donald ";
	char src[255] = "Trump";
	my_strcat(dst, src);
	printf("%s\n", dst);
	return 0;
}
