#include <stdio.h>
#include <math.h>
#include <limits.h>

int main(int argc, char** argv) {

    printf("--------Assuming 2-complement--------\n");
    printf("-----------Computed limits-----------\n");
    
    printf("Unsigned Char max   :   %d\n", (unsigned char) ~0);
    printf("Unsigned short max  :   %d\n", (unsigned short) ~0);
    printf("Unsigned int max    :   %u\n", (unsigned int) ~0);
    printf("Unsigned long max   :   %lu\n", (unsigned long) ~0);

    printf("Signed char max     :   %d\n", (char) ((unsigned char) ~0 >> 1));
    printf("Signed char min     :   %d\n", -(char) (unsigned char) 1 << ((sizeof(unsigned char) * CHAR_BIT) - 1));
    printf("Signed short max    :   %d\n", (short) ((unsigned short) ~0 >> 1));
    printf("Signed short min    :   %d\n", -(short) (unsigned short) 1 << ((sizeof(unsigned short) * CHAR_BIT) - 1));
    printf("Signed int max      :   %d\n", (int) ((unsigned int) ~0 >> 1));
    printf("Signed int min      :   %d\n", -(int) (unsigned int) 1 << ((sizeof(unsigned int) * CHAR_BIT) - 1));
    printf("Signed long max     :   %ld\n", (long) ((unsigned long) ~0 >> 1));
    printf("Signed long min     :   %ld\n", -(long) (unsigned long) 1 << ((sizeof(unsigned long) * CHAR_BIT) - 1));

    
    int i;

    union {
        int i;
        float f;
    } uf;
    float f;
    for (f = 1; f < INFINITY; uf.f = f, f *= 1e1);
    unsigned int i1 = (unsigned int) ~0;
    float f1 = (float) i1;
    for (i = 2, f = uf.f; f * i < INFINITY; uf.f = f * i, i++);
    uf.i = uf.i | 0x7FFFFFu; // Mantissa for float is 23 bit on my machine
    printf("FLT max     :   %g (float)\n", uf.f);
    printf("-FLT max    :   %g (float)\n", -uf.f);
    uf.i = uf.i & 0u;
    uf.i = uf.i | 0x7FFFFFu;
    printf("FLT min     :   %g (float)\n", uf.f);
    printf("-FLT min    :   %g (float)\n", -uf.f);

    union {
        long int i;
        double d;
    } ud;
    double d;
    for (d = 1; d < INFINITY; ud.d = d, d *= 1e1);
    for (i = 2, d = ud.d; d * i < INFINITY; ud.d = d * i, i++);
    ud.i = ud.i | 0xFFFFFFFFFFFFFlu; // Mantissa for double is 52 bit on my machine
    printf("DBL max     :   %g (double) \n", ud.d);
    printf("-DBL max    :   %g (double)\n", -ud.d);
    ud.i = ud.i & 0u;
    ud.i = ud.i | 0xFFFFFFFFFFFFFlu;
    printf("DBL min     :   %g (double)\n", ud.d);
    printf("-DBL min    :   %g (double)\n", -ud.d);
    
    return 0;
}
