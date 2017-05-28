#include <stdio.h>

unsigned invert2(unsigned x, int p, int n);
unsigned invert(unsigned x, int p, int n);

int main(int argc, char** argv) {

    unsigned x = ~0;
    unsigned r;

    printf("x = %u\n", x);

    printf("Invert 16 bits from 32nd position on\n");
    r = invert(x, 31, 16);
    printf("%u\n", r);

    printf("Invert 16 bits from 16th position on\n");
    r = invert2(x, 15, 16);
    printf("%u\n", r);

    return 0;
}

unsigned invert(unsigned x, int p, int n) {

   unsigned mask = ~(~0 << n) << (p - n + 1);
   x = x ^ mask;
 

   return x;
}


/* without using xor */
unsigned invert2(unsigned x, int p, int n) {
    
    unsigned y = ((~(x >> (p - n + 1)) & ~(~0 << n)) << (p - n + 1));
    unsigned mask = ~(~0 << n) << (p - n + 1);
    x = x & ~mask;
    x = x | y;

    return x;
}

