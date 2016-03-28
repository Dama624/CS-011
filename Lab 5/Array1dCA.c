#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "memcheck.h"

/*
 * This program prints a one-dimensional cellular automata that follows the
 * following rules:
 * 1) If the current cell is empty, and one of the two adjacent cells is full 
 * (but not both), set the current cell to be full.
 *
 * 2) Otherwise set the current cell to be empty.
 *
 * The program takes two command line arguments:
 * "program name" [number of cells in the 1dCA] [number of generations]
 * 
 * The 1dCA will have two states ("." and "*"). The 1dCA will be randomly
 * seeded with an approximately 50-50 distribution of the states, and the
 * program will run given the rules for the input number of generations. Each
 * generation will be printed onto the command line.
*/

void usage(char *name) /* Usage message */
{
    fprintf(stderr, "usage: %s [number of cells] [number of generations]\n", \
    	name);
}

int random1or0(void) /* Randomly returns 1 or 0 at a ~50-50 rate */
{
    if (rand() % 2 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void printgeneration(int gen[], int length) /* Prints the input generation */
{
    int i;
    for (i = 0; i < length; i++)
    {
        if (gen[i] == 0)
        {
            printf(".");
        }
        else
        {
            printf("*");
        }
    }
    printf("\n");
}

void initializegen(int gen[], int length) /* Initializes the generation */
{
    int i;
    gen[0] = 0;
    for (i = 1; i < (length - 1); i++)
    {
        gen[i] = random1or0();
    }
    gen[(length - 1)] = 0;
}

void updategen(int currentgen[], int length)
{
    /* Takes the current generation and returns the next generation as
    updated according to the 1dCA rules listed in the program description */
    int *next_gen; /* Initialize the next gen */
    int i;
    /* Allocate memory for the array of next_gen */
    next_gen = (int *)calloc(length, sizeof(int));
    /* Check that the calloc call succeeded. */
    if (next_gen == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);  /* abort the program */
    }
    next_gen[0] = 0;
    next_gen[(length - 1)] = 0;
    for (i = 1; i < (length - 1); i++)
    {
        if (currentgen[i] == 0 && \
            ((currentgen[i - 1] == 1 && currentgen[i + 1] == 0) || \
            (currentgen[i - 1] == 0 && currentgen[i + 1] == 1)))
        {
            next_gen[i] = 1;
        }
        else
        {
            next_gen[i] = 0;
        }
    }
    for (i = 0; i < length; i++) /* Assign next_gen to currentgen */
    {
        currentgen[i] = next_gen[i];
    }
    free(next_gen); /* Free the memory taken by updategen */
}

int main(int argc, char *argv[])
{
    int *currentgen; /* Initialize the current generation */
    int length; /* Initialize the length of the 1dCA */
    int gens; /* Initialize the number of generations */
    int i;
    if (argc != 3) /* Return usage if # of args is incorrect */
    {
        usage(argv[0]);
        exit(1);
    }
    srand(time(NULL));
    length = atoi(argv[1]);
    gens = atoi(argv[2]);
    currentgen = (int *)calloc(length, sizeof(int));
    if (currentgen == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);  /* abort the program */
    }
    initializegen(currentgen, length); /* We now have the starting gen */
    printgeneration(currentgen, length); /* Print the starting gen */
    for (i = 0; i < (gens - 1); i++) /* Loop through each generation */
    {
        updategen(currentgen, length); /* Update the board */
        printgeneration(currentgen, length); /* Print it */
    }
    free(currentgen); /* Free the memory taken by currentgen */
    print_memory_leaks();
    return 0;
}
