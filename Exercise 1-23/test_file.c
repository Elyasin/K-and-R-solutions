/* 
 * File:   test_file.c
 * Author: Prog Rammer
 *
 * Created on January 1, 1970, 00:00:00 UTC 
 */

// Include standard input/output header
#include <stdio.h>
// Include standard library header
#include <stdlib.h>

/*
 * This is a function.
 */
int printf_strings(int argc, char** argv) {

    // This are quoted strings, not comments
    char *s1 = "//This comment is a quoted string";
    char *s2 = "/* This is another quoted string */";

    //print the strings
    printf("%s\n", s1);
    printf("%s\n", s2);

    // return success
    return 0;
}

