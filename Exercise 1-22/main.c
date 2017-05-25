/*
 * Exercise 1-22
 * Write a program to “fold” long input lines into two or more shorter lines 
 * after the last non-blank character that occurs before the n-th column of 
 * input. Make sure your program does something intelligent with very long 
 * lines, and if there are no blanks or tabs before the specified column.
 * 
 */

#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8   //change this to your system's tabstop size
#define FOLD_COL    80  //adapt n-th column to fold at

int get_line(char line[], int maxline);
int detab(char to[], char from[]);
void fold(char to[], char from[]);

main() {
    int len;
    char line[MAXLINE];
    char folded_line[MAXLINE];
    char detabbed_line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        len = detab(detabbed_line, line);
        if (len < FOLD_COL) {
            printf("%s", detabbed_line);
        } else {
            fold(folded_line, detabbed_line);
            printf("%s", folded_line);
        }
    }
    return 0;
}

int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') s[i++] = c;
    s[i] = '\0';
    return i;
}


void fold(char dest[], char source[]) {
    int c, i, j, k;
    int counter = 0;

    for (i = j = 0; (c = source[i]) != EOF && c != '\n'; i++) {
        counter++;
        if (counter == FOLD_COL) {  /* fold text here */
            if (c == ' ') {         /* fole at white space */
                dest[j++] = '\n';
                counter = 0;
                for (; isspace(source[i]); i++) /* start next line without white space ? */
                    ;  
                i--;
                continue;
            } else {
                for (k = j + 1; dest[k] != ' ' && dest[k] != '\t' && k > 0; k--)    /* find first white space backwards */
                    for (; dest[k] == ' ' && dest[k] == '\t'; k--)
                        ;
                if (k != 0) { // text has white space, fold line 
                    dest[k] = '\n';
                    counter = j - k;
                } else {    /* long contiguous text without white space */
                   for ( ; !isspace(source[i]) ; i++)   /* ignore text until next non white space */ 
                       ;
                   dest[j] = '.';
                   dest[j-1] = '.';
                   dest[j-2] = '.';
                   j++;
                   continue;
                }
            }
        }
        dest[j++] = c;
    }
    if (c == '\n') {
        dest[j++] = c;
    }
    dest[j] = '\0';
}


int detab(char to[], char from[]) {
    int c, i, j, k, spaces;

    for (i = 0, k = 0; (c = from[i]) != EOF && c != '\n'; ++i, ++k) {
        if (c == '\t') {
            spaces = TABSTOP - k % TABSTOP;
            for (j = 1; j <= spaces; ++j) {
                to[k++] = ' ';
            }
            --k;
        } else
            to[k] = c;
    }
    if (c == '\n') 
        to[k++] = c;
    to[k] = '\0';
    return k-1;
}
