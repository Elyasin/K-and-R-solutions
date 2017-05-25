/* 
 * Exercise 1-13 Horizontal
 * Write a program to print a histogram of the lengths of words in its input.
 * It is easy to draw the histogram with the bars horizontal; a vertical 
 * orientation is more challenging.
 */

#include <stdio.h>

int main() {
    int i, c, lcounter = 0;
    int histo[11];

    for (i = 0; i < 11; i++) histo[i] = 0;

    while ((c = getchar()) != EOF) {
        if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')) {
            if (lcounter >= 11) lcounter = 10;
            histo[lcounter] = histo[lcounter] + 1;
            lcounter = 0;
        } else {
            ++lcounter;
        }
    }

    for (i = 1; i < 11; i++) {
        int j;
        printf("%2d ", i);
        for (j = 0; j < histo[i]; j++) printf("X");
        printf("\n");
    }

}
