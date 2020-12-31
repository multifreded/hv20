#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define IN_BUF_SIZE 20
#define OUT_BUF_SIZE 4

void calc_hash(char *src_buf,int len,uint32_t *sink_buf)
{
	uint32_t blk_a0, blk_b0;
	uint32_t blk_a1, blk_b1;
	uint32_t blk_a2, blk_b2;
	uint32_t blk_a3, blk_b3;

	uint32_t i;
	char     chr;
	
	blk_a0 = 0x68736168; blk_b0 = 0xc00ffeee;
	blk_a1 = 0xdeadbeef; blk_b1 = 0x68736168;
	blk_a2 = 0x65726f6d; blk_b2 = 0xdeadbeef;
	blk_a3 = 0xc00ffeee; blk_b3 = 0x65726f6d;

	i = 0;
	while (i < len) {
		chr = src_buf[i];
		blk_a1 = blk_b1 ^
		         ((uint32_t)chr *  i         & 0xffU ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0x31) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0x42) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0xef) & 0xffU ^ (uint32_t)chr) << 8);
		blk_a2 = blk_b2 ^
		         ((uint32_t)chr *  i         & 0x5aU ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0xc0) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0x11) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0xde) & 0xffU ^ (uint32_t)chr) << 8);
		blk_a3 = blk_b3 ^
		         ((uint32_t)chr *  i         & 0x22U ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0xe3) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0xde) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0x0d) & 0xffU ^ (uint32_t)chr) << 8);
		blk_a0 = blk_b0 ^
		         ((uint32_t)chr *  i         & 0xefU ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0x52) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0x24) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0x33) & 0xffU ^ (uint32_t)chr) << 8);
		i = i + 1;
		blk_b0 = blk_a0;
		blk_b3 = blk_a3;
		blk_b2 = blk_a2;
		blk_b1 = blk_a1;
	}

	sink_buf[0] = blk_a0;
	sink_buf[1] = blk_a1;
	sink_buf[2] = blk_a2;
	sink_buf[3] = blk_a3;

	return;
}


int main() {
	char     in_buf[IN_BUF_SIZE];
	uint32_t out_buf[OUT_BUF_SIZE];
	int      str_len = 0;

	fgets(in_buf, sizeof in_buf, stdin);
	for(int i=0; i < IN_BUF_SIZE; i++) {
		if(in_buf[i] == 0x00 || in_buf[i] == 0x0a) {
			str_len = i;
			break;
		}
	}

	calc_hash(in_buf, str_len, out_buf);

	fwrite(out_buf, 1, sizeof(out_buf), stdout);

	return 0;
}
