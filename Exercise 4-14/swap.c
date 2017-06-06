#include <stdio.h>

#define swap(t,x,y) { t var_t; var_t = x; x = y; y = var_t; }
main() {

    int i1 = 1, i2 = 2;
    float f1 = 0.1, f2 = 0.2;
    double d1 = 1.1, d2 = 9.9;

    printf("Before: %d, %d\n", i1, i2);
    swap(int, i1, i2);
    printf("Swapped: %d, %d\n", i1, i2);

    printf("Before: %f, %f\n", f1, f2);
    swap(float, f1, f2);
    printf("Swapped: %f, %f\n", f1, f2);

    printf("Before: %lf, %lf\n", d1, d2);
    swap(double, d1, d2);
    printf("Swapped: %lf, %lf\n", d1, d2);

    return 0;
}
