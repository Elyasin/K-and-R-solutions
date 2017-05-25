/*
 * Exercise 1-2
 * Experiment to find out what happens when printf’s argument string contains 
 * \c, where c is some character not listed above.
 * 
 */

#include <stdio.h>

/*
 * https://en.wikipedia.org/wiki/Escape_sequences_in_C
 * 
 * \z - might give a warning. prints the letter z.
 * \x - will not compile.
 * \0 - no warning. compiles.
 * ...
 * 
 */
main() {
    printf("hello, world\z");
}
