/*
 * Exercise 1-4
 * Write a program to print the corresponding Celsius to Fahrenheit table.
 */

#include <stdio.h>

main() {
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 150;
    step = 10;

    celsius = lower;
    printf("%7s %10s\n", "Celsius", "Fahrenheit");
    printf("%7s %10s\n", "-------", "----------");
    while (celsius <= upper) {
        fahr = (celsius * 9.0 / 5.0) + 32.0;
        printf("%7.0f %10.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

