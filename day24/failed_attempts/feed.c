#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define IN_BUF_SIZE 20
#define OUT_BUF_SIZE 4

int main() {
	char in_buf[IN_BUF_SIZE];
	uint32_t out_buf[OUT_BUF_SIZE];
	char c;
	int  i = 0;
	int  str_len = 0;

	/*
	for (int i=0; i < IN_BUF_SIZE; i++) {
		in_buf[i] = 0x00;
	}

	for (int i=0; i < OUT_BUF_SIZE; i++) {
		out_buf[i] = 0x00000000;
	}
	*/

	
	while ((c = getchar()) != EOF) {
		if (i >= IN_BUF_SIZE || c == 0x0a) {
			printf("ladida\n%s\n0\n3\n", in_buf);
			i = 0;
		} else {
			in_buf[i] = c;
			i++;
		}
	}

	return 0;
}
