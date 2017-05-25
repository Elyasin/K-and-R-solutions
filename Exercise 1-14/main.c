/* 
 * Exercise 1-14
 * Write a program to print a histogram of the frequencies of different 
 * characters in its input.
 */

#include <stdio.h>

int main() {
    int i, c, lcounter = 0;
    int histo['z'-'a'];

    for (i = 0; i <= 'z'-'a'; i++) histo[i] = 0;

    // A = 65
    // Z = 90
    // a = 97
    // z = 122
    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') {
            histo[c-'a'] += 1;
        } else if (c >= 'A' && c <= 'Z') {
            histo[c-'A'] += 1;
        }
    }

    printf("\n");
    for (i = 0; i <= 'z'-'a'; i++) {
        int j;
        printf("%2c ", i+'a');
        for (j = 0; j < histo[i]; j++) printf("X");
        printf("\n");
    }
    

}
