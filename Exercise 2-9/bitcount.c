#include <stdio.h>

int bitcount(unsigned x);

int main(int argc, char** argv) {

    int x = 2576980377;
    int b;

    b = bitcount(x);
    printf("%d\n", b);

    return 0;
}

int bitcount(unsigned x) {

    int b;

    for (b = 0; x != 0; x &= (x - 1))
        b++;

    return b;
}
