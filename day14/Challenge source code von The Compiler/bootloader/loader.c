#include <stdio.h>
#include "qrdata.h"

#define qr_width 25
#define qr_height 13

int main(void) {
  for (unsigned int i = 0; i < qr_width * qr_height; i++) {
    int bitoffset = 2 * (i % 4);  // 0, 2, 4, 6
    int mask = 0b11 << bitoffset;
    int idx = i / 4;
    int value = (qr_code[idx] & mask) >> bitoffset;

    //printf("i = %d, bitoffset = %d, idx = %d --> %x\n", i, bitoffset, idx, value);
    //if (i == qr_width*4) {
    //  return 1;
    //}

    if (i % qr_width == 0) {
      putc('\n', stdout);
    }

    putc(lut[value], stdout);
  }
}
