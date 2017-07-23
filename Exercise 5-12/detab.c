#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8
#define YES     1
#define NO      0

void settab(int argc, char *argv[], char *tab);
int tabpos(int pos, char *tab);
int get_line(char line[], int maxline);
void detab(char to[], char from[]);

char tab[MAXLINE];

main(int argc, char *argv[]) {
    int len;
    char line[MAXLINE];
    char detabbed_line[MAXLINE];

    settab(argc, argv, tab);

    while ((len = get_line(line, MAXLINE)) > 0) {
        detab(detabbed_line, line);
        printf("%s", detabbed_line);
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

void detab(char to[], char from[]) {
    int c, i, k, pos, spaces;

    pos = 0;
    for (i = 0, k = 0; (c = from[i]) != EOF && c != '\n'; ++i, ++k) {
        if (c == '\t') {
            do
		to[k++] = ' ';
	    while (tabpos(++pos, tab) == NO);
	    k--;
        } else {
            to[k] = c;
            ++pos;
        }
    }
    if (c == '\n') 
        to[k++] = c;
    to[k] = '\0';
}
