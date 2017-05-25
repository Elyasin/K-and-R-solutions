/*
 * Exercise 1-3
 * Modify the temperature conversion program to print a heading above the table.
 */

#include <stdio.h>

main() {
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("%10s %10s\n", "Fahrenheit", "Celsius");
    printf("%10s %10s\n", "----------", "-------");
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%10.0f %10.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

