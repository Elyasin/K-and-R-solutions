#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, int n);

int main(int argc, char** argv) {

    unsigned x = 170;

    x = rightrot(x, 2);
    printf("%u\n", x);

    return 0;
}

unsigned rightrot(unsigned x, int n) {

    unsigned x_right = x >> n;
    unsigned x_left = x << ((sizeof (unsigned) * CHAR_BIT) - n);
    x = x_right | x_left;

    return x;
}
