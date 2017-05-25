/* 
 ( File:   main.c
 ( Author: elyasin 
 (
 ( Created on July 30, 2015, 9:00 AM
 */

// Include (standard) input/output header
#include <stdio.h>
// Include (standard) library header
#include <stdlib.h>

/*
 * This is a the main function.
 */
int printf_strings(int argc, char** argv) {

    // This are quoted strings, not comments
    char *s1 = "// This comment is a \"quoted\" string :-)";
    char *s2 = "/* This is another \'quoted\' string */ :-]";
    char *s3 = "/* This is another \'quoted\' string */ :-}";
    
    //print the strings
    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s2);
    
    // return success :-)
    return 0;
}

