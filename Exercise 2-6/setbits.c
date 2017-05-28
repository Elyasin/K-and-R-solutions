#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(int argc, char** argv) {

    unsigned x = 255;
    unsigned y = 205;
    unsigned r;

    r = setbits(x, 5, 2, y);
    printf("%u\n", r);

    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {

    unsigned mask = ~(~0 << n) << (p - n + 1);
    x = x & ~mask;
    y = (y & ~(~0 << n)) << (p - n + 1);
    x = x | y;

    return x;
}
