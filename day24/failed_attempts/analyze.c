#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define IN_BUF_SIZE 1000
#define NL_TILL_DATA 10

int main() {
	char in_buf[IN_BUF_SIZE];
	char c;
	int nls = 0;
	int  i = 0;

	while ((c = getchar()) != EOF) {
		if (nls == NL_TILL_DATA) {
			in_buf[i] = c;
			i++;
		}

		if (c == 0x0a) {
			nls++;
			if (nls > NL_TILL_DATA) {
				in_buf[i] = 0x00;
			}
		}
	}

	printf("%s", in_buf);
	remove("data/ladida_pwd.txt");

	return 0;
}
