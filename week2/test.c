#include <stdio.h>
#include <string.h>

int main() {
	char* str1 = "Donald";
	char* str2 = "Donald";

	char* p;
	if(str1 == str2) {
		p = "Same";
	} else {
		p = "Different";
	}
	printf("%s\n", p);
	return 0;
}
