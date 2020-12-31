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
}


void decrypt(uint32_t *hash_buf) {
	unsigned char enc_data_buf[32] = {0x0a,0x11,0x48,0x43,0xde,0x12,0x0e,0x14,0xce,0xa0,0x6e,0xa7,0x49,0xcd,0x8e,0x80,0x35,0x08,0x0d,0x53,0xc1,0x6d,0x1a,0x68,0x84,0xeb,0x28,0xa0,0x27,0x8a,0x8f,0xa4};
//	unsigned char enc_data_buf[32] = {0xe5,0xaf,0xe5,0x9d,0x31,0xac,0xa3,0xca,0x21,0x1e,0xc3,0x79,0xa6,0x73,0x23,0x5e,0xda,0xb6,0xa0,0x8d,0x2e,0xd3,0xb7,0xb6,0x6b,0x55,0x85,0x7e,0xc8,0x34,0x22,0x00};
	unsigned char dec_data_buf[32] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//	unsigned char enc_data_buf[14] = {0xbb,0x78,0xaf,0x6d,0x51,0x9a,0x11,0xa7,0x49,0x0f,0x74,0x66,0x87,0x4a};
//	unsigned char dec_data_buf[14] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	int           data_len =   32;

	unsigned char magic[10] = {0xde,0xad,0xbe,0xef,0xc0,0x12,0x34,0x56,0x78,0x9a};
	unsigned char hash_byte;
	unsigned char magic_byte;
	unsigned char key_byte;

	for(int i=0; i < data_len; i++) {
		hash_byte = ( hash_buf[(i % 16) / 4] >> (8 * (i % 4)) ) & 0xff;
		//printf("%02x ", hash_byte);
		magic_byte = magic[hash_byte % 10];
		//printf("%02x ", magic_byte);
		key_byte = hash_byte ^ magic_byte ^ (unsigned char) i;
		//printf("%02x ", key_byte);

		dec_data_buf[i] = key_byte ^ enc_data_buf[i];
	}

	fwrite(dec_data_buf, 1, data_len, stdout);
	printf("\n");
}


int main() {
	char str_buf[IN_BUF_SIZE];
	uint32_t hash_buf[OUT_BUF_SIZE];
	char c;
	int  i = 0;

	while ((c = getchar()) != EOF) {
		if (c == 0x0a) {
			str_buf[i] = 0x00;
			calc_hash(str_buf, i, hash_buf);
//			printf("\nPassword:%s\n", str_buf);
			decrypt(hash_buf);
			i = 0;
		} else {
			if (i < IN_BUF_SIZE) {
				str_buf[i] = c;
				i++;
			}
		}
	}

	return 0;
}
