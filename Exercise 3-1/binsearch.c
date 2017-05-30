#include <stdio.h>

// Adjust MAXSIZE to your computer's capacities
#define MAXSIZE 600000000

int binsearch(int x, int v[], int n);

int main(int argc, char** argv) {


    static int v[MAXSIZE]; //allocate array on the heap by making it static
    int x = MAXSIZE; // not in the array - out of bounds
    int r, i;

    for (i = 0; i < MAXSIZE; i++)
        v[i] = i;

    r = binsearch(x, v, MAXSIZE);
    printf("Element at position: %d\n", r);

    return 0;
}

int binsearch(int x, int v[], int n) {

    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

