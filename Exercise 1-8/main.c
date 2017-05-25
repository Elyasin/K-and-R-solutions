/* 
 * Exercise 1-8
 * Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

main() {
    int c, nlc, tc, bc;
    
    nlc = tc = bc = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') nlc++;
        if (c == '\t') tc++;
        if (c == ' ') bc++;
    }
    printf("\n");
    printf("\\n : %d\n", nlc);
    printf("\\t : %d\n", tc);
    printf("\' \': %d\n", bc);
}

