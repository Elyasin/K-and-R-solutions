/* 
 * Exercise 1-15
 * Rewrite the temperature conversion program of Section 1.2 to use a function 
 * for conversion.
 */

#include <stdio.h>

void displayTemperatureTable(float fahr, float max, float step) {
    float celsius;
    printf("%10s %10s\n", "Fahrenheit", "Celsius");
    printf("%10s %10s\n", "----------", "-------");
    while (fahr <= max) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%10.0f %10.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

main() {
    displayTemperatureTable(0, 300, 20);
}