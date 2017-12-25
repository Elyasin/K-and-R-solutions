#include <stdio.h>
#include <string.h>
#include <fcntl.h>      /* flags for read and write */
#include <sys/types.h>  /* typedefs */
#include <sys/stat.h>   /* structure returned by stat */
#include <dirent.h>     /* use C library for directory interface */

void fsize(char *);

/* printf file sizes */
int main(int argc, char *argv[]) {

    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);

    return 0;
}

void dirwalk(char *, void (*fcn)(char *));

/* fsize: print size of file name */
void fsize(char *name) {

    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ( (stbuf.st_mode & S_IFMT) == S_IFDIR ) 
        dirwalk(name, fsize);
    printf("%8ld ", stbuf.st_ino);
    printf("%8ld ", stbuf.st_size);
    printf("%3lu ", (unsigned long int) stbuf.st_nlink); /* to avoid warning on my architecture */
    printf("%4d ", stbuf.st_uid);
    printf("%4d ", stbuf.st_gid);
    printf("%c", ((stbuf.st_mode & S_IFMT) == S_IFDIR) ? 'd' : '-' );
    printf("%c", (stbuf.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (stbuf.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (stbuf.st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (stbuf.st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (stbuf.st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (stbuf.st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (stbuf.st_mode & S_IROTH) ? 'r' : '-');
    printf("%c", (stbuf.st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (stbuf.st_mode & S_IXOTH) ? 'x' : '-');
    printf("  %s\n", name);

}

#define MAX_PATH 1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *)) {

    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ( (dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    
    while ( (dp = readdir(dfd)) != NULL ) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        if ( strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name) )
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

