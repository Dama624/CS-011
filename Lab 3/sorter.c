#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MAX_ARGS 32 /* Maximum number of arguments allowed by program. */

/* This program sorts integers (from smallest to largest) given in the
* command line in the form:
* "program name" [-b] [-q] number 1 [number2 ... ].
* The maximum number of integers allowed is defined as MAX_ARGS in the
* preprocessor.
* The default sorting algorithm is the Minimum Element Sort.
* [-b]: Uses Bubble Sort instead of Minimum Element Sort.
* [-q]: Suppresses the output (i.e. nothing gets printed).
* Values are printed one per line. */

void usage(char *name) /* Usage message */
{
    fprintf(stderr, "usage: %s [-b] [-q] number1 [number2 ... ] \
        (maximum %d numbers)\n", name, MAX_ARGS); 
}

void minsort(int array[], int num_elements) /* Minimum Element Sort Algorithm */
{
    /* smallest stores the index of the smallest element found so far */
    int start;
    int index;
    int swap; /* Temp. variable for swapping elements in a list */
    for (start = 0; start < num_elements; start++)
    {
        int smallest = start;
        for (index = start; index < num_elements; index++)
        {
            /* go through array */
            if (array[index] < array[smallest])
            {
                /* check if value is smaller */
                smallest = index; /* index of smaller value recorded */
            }
        }
        /* index of smallest value is "smallest" */
        /* start value and smallest value are swapped */
        swap = array[start];
        array[start] = array[smallest];
        array[smallest] = swap;
        /* start index increased by 1 */
    }
    /* Check that the array is sorted correctly. */
    for (index = 1; index < num_elements; index++)
    {
        assert(array[index] >= array[index - 1]);
    }
}

void bubblesort(int array[], int num_elements) /* Bubble Sort Algorithm */
{
    int isswapped = 1; /* Boolean value for whether a swap occurred */
    int index;
    int swap; /* Temp. variable for swapping elements in a list */
    while (isswapped == 1)
    {
        isswapped = 0; /* Will break the while loop if no swap occurs */
        for (index = 1; index < num_elements; index++)
        {
            /* Loop through array */
            if (array[index - 1] > array[index])
            {
                /* Checking if next index value is greater than current */
                /* If so, swap the two positions */
                swap = array[index - 1];
                array[index - 1] = array[index];
                array[index] = swap;
                /* To remember that a swap occurred this loop */
                isswapped = 1;
            }
        }
    }
    /* Check that the array is sorted correctly. */
    for (index = 1; index < num_elements; index++)
    {
        assert(array[index] >= array[index - 1]);
    }
}

int main(int argc, char *argv[]) /* Command line input stuffs */
{
    int i;
    int quiet = 0; /* Value for the "-q" optional argument */
    int bubble = 0; /* Value for the "-b" optional argument */
    int numcnt = 0; /* Count the number of integers in the input */
    int storedints[MAX_ARGS]; /* Create an array for all the integer inputs */
    int j = 0;
    if (argc == 0) /* Return usage if there are no arguments at all */
    {
        usage(argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-q") == 0) /* Processing "-q" optional arg. */
        {
        quiet = 1; /* Used as a boolean value. */
        }
        else if (strcmp(argv[i], "-b") == 0)
        {
            bubble = 1; /* Used as a boolean value. */
        }
        else
        {
            numcnt++;
        }
    }
    if (numcnt > MAX_ARGS || numcnt == 0)
    {
        /* If the number of integers in the input is greater than MAX_ARGS
        * or = 0 */
        usage(argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++) /* Cycle through command line input again */
    {
        if ((strcmp(argv[i], "-q") != 0) && (strcmp(argv[i], "-b") != 0))
        {
            /* If the read argument is a number */
            /* Assign number to array element */
            storedints[j] = atoi(argv[i]);
            j++;
        }
    }
    if (bubble == 1) /* If [-b] was specified in the input */
    {
        bubblesort(storedints, numcnt);
    }
    else
    {
        minsort(storedints, numcnt);
    }
    if (quiet == 0) /* If [-q] was NOT specified in the input */
    {
        for (j = 0; j < numcnt; j++)
        {
            printf("%d\n", storedints[j]);
        }
    }
    return 0;
}
