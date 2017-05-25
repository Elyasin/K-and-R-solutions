/* 
 * Exercise 1-13 Horizontal
 * Write a program to print a histogram of the lengths of words in its input.
 * It is easy to draw the histogram with the bars horizontal; a vertical 
 * orientation is more challenging.
 */

#include <stdio.h>

int main() {
    int i, j, c, max = 0, lcounter = 0;
    int histo[11];

    for (i = 0; i < 11; i++) histo[i] = 0;

    while ((c = getchar()) != EOF) {
        if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')) {
            if (lcounter >= 11) lcounter = 10;
            histo[lcounter] = histo[lcounter] + 1;
            if (histo[lcounter] > max) max = histo[lcounter];
            lcounter = 0;
        } else {
            ++lcounter;
        }
    }

    printf("\n");
    for (i = max; i > 0; i--) {
        for (j = 1; j < 11; j++) {
            if (i <= histo[j])
                printf("%3c", 'X');
            else
                printf("%3c", ' ');
        }
        printf("\n");
    }
    for (i = 1; i<11; i++) printf("%3d", i);

    printf("\n");
}
