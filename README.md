# K-and-R-solutions

Exercise solutions for The C Programming Language, 2nd edition

You will find sometimes a file named lorem_ipsum.txt (or similar) that you can use for testing.

For example, if `a.out` is the executable then you could do something like `./a.out < lorem_ipsum.txt`.

## Exercise 4-5, 4-6, 4-10 and 4-11
This program uses the math library functions `sin`, `exp` and `pow`; make sure you link with the math library, e.g. `gcc calculator.c -lm`.

## Exercise 5-7
You can test the program like this `./a.out < lines.txt`. `lines.txt` is a long computer science poetry.
You can time it like so `time ./a.out < lines.txt`.

## Exercise 5-11 and 5-12
Similar to 5-7, but you'll find two files; one for testing `detab` and one for `entab`.

## Exercise 5-13
Similar to 5-7.

## Exercise 6-1
You can test by giving the getword.c program itself as input: `./a.out < getword.c`

## Exercise 6-3 and 6-4
You can use a long Computer Science poem as input for test: `./a.out < cs_poetry.txt` (or the source code as in 6-1)

## Exercise 6-5
You can test by giving the source code as input: `./a.out < preprocessor.c`

## Exercise 7-1
You can test with the text file as input: `./a.out  tolower < lines.txt` (or `toupper` for upper case conversion)

## Exercise 7-5
I opted for a little unusual solution. The result is only displayed when requested via the character 'p' (print).

## Exercise 7-7
You can use one or all the three files for testing: file1.txt, file2.txt, file3.txt

## Exercise 7-8
You'll find two Computer Science poems in the folder.


