#define MAXLINE 1000
#define YES     1

int tabpos(int pos, char *tab) {

    if (pos >= MAXLINE)
        return YES;
    else
        return tab[pos];
}
