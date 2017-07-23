#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8
#define YES     1
#define NO      0

void settab(int argc, char *argv[], char *tab);
int tabpos(int pos, char *tab);
int get_line(char line[], int maxline);
void entab(char to[], char from[]);

char tab[MAXLINE];

main(int argc, char *argv[]) {
    int len;
    char line[MAXLINE];
    char entabbed_line[MAXLINE];

    settab(argc, argv, tab);

    while ((len = get_line(line, MAXLINE)) > 0) {
        entab(entabbed_line, line);
        printf("%s", entabbed_line);
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

void entab(char to[], char from[]) {
    int c, i, j, tabs, spaces, pos;

    spaces = tabs = 0;
    for (i = j = pos = 0; (c = from[i]) != EOF && c != '\n'; i++, pos++) {
        if (c == ' ') {
            //if ((pos + 1) % TABSTOP == 0) {
            if ( tabpos(pos+1, tab) == YES ) {
                tabs++;
                spaces = 0;
            } else {
                spaces++;
            }
        }
        if (c != ' ') {
            for (; tabs > 0; tabs--, j++)
                to[j] = '\t';
            tabs = 0;
            if (c == '\t') {
                spaces = 0;
                //pos = pos + (TABSTOP - pos % TABSTOP) - 1;
                for ( ; tab[pos+1] != YES; pos++, j++) {
                    to[j] = ' ';
                }
            }
            for (; spaces > 0; spaces--, j++)
                to[j] = ' ';
            to[j++] = c;
        }
    }
    if (c == '\n') {
        to[j++] = c;
    }
    to[j] = '\0';
}
