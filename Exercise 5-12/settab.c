#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8
#define YES     1
#define NO      0


void settab(int argc, char *argv[], char *tab) {
    
    int i, pos, inc;

    if (argc <= 1)
        for (i = 1; i < MAXLINE; i++)
            if ( i % TABSTOP == 0)
                tab[i] = YES;
            else
                tab[i] = NO;
    else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+') {
        pos = atoi(&(*++argv)[1]);
        inc = atoi(&(*++argv)[1]);
        for (i = 1; i < MAXLINE; i++)
            if (i!=pos)
                tab[pos] = NO;
            else
                tab[i] = YES, pos += inc;
    } else {
        for (i = 1; i < MAXLINE; i++) 
            tab[i] = NO;
        while (--argc > 0) {
            pos = atoi(*++argv);
            if ( pos > 0 && pos <= MAXLINE)
            tab[pos] = YES;
        }
    }
}
