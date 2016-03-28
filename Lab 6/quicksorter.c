#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "memcheck.h"
#include "linked_list.h"

/* This program sorts integers (from smallest to largest) given in the
* command line in the form:
* "program name" [-b] [-q] number 1 [number2 ... ].
* The sorting algorithm used is quicksort.
* [-q]: Suppresses the output (i.e. nothing gets printed).
* Values are printed one per line. */

void usage(char *name) /* Usage message */
{
    fprintf(stderr, "usage: %s [-q] number1 [number2 ... ] \n", name); 
}

node *quicksort(node *input)
{
    node *sorted_list;
    /* Check if the input list is empty or one node */
    if (input == NULL || input->next == NULL)
    {
        /* Create a copy of the list */
        node *copy; /* Pointer to a copy of the input list */
        copy = copy_list(input); /* Make a copy of the input list */
        return copy;
    }
    else
    {
        node *copynode;
        node *n;
        node *largerthan;
        node *largerthanhead;
        node *smallerthan;
        node *smallerthanhead;
        node *largerthanpivot;
        node *smallerthanpivot;
        node *halfsortedlist;
        largerthanhead = NULL;
        smallerthanhead = NULL;
        /* Create a copy of the first node */
        copynode = create_node(input->data, NULL);
        for (n = (input->next); n != NULL; n = n->next)
        {
            /* Check for nodes with values larger than or
             * equal to 1st node */
            if (n->data >= copynode->data)
            {
                largerthan = create_node(n->data, largerthanhead);
                largerthanhead = largerthan;
            }
            /* Check for nodes with values less than
             * the 1st node */
            if (n->data < copynode->data)
            {
                smallerthan = create_node(n->data, smallerthanhead);
                smallerthanhead = smallerthan;
            }
        }
        /* Sort the two lists recursively */
        largerthanpivot = quicksort(largerthanhead);
        smallerthanpivot = quicksort(smallerthanhead);
        /* Free memory from largerthan & smallerthan */
        free_list(largerthanhead);
        free_list(smallerthanhead);
        /* Append the sorted sublists in order from smallest -> largest */
        halfsortedlist = append_lists(copynode, largerthanpivot);
        sorted_list = append_lists(smallerthanpivot, halfsortedlist);
        free_list(largerthanpivot);
        free_list(copynode);
        free_list(halfsortedlist);
        free_list(smallerthanpivot);
    }
    assert(is_sorted(sorted_list));
    return sorted_list;
}

int main(int argc, char *argv[]) /* Command line input stuffs */
{
    node *input; /* pointer to input list */
    node *temp; /* temporary pointer to node */
    node *finalsort; /* Final sorted list */  
    int i;
    int quiet; /* Value for the "-q" optional argument */
    input = NULL;
    quiet = 0;
    if (argc == 0) /* Return usage if there are no arguments at all */
    {
        usage(argv[0]);
        exit(1);
    }
    /* Account for the "-q" optional arg. */
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-q") == 0) /* Processing "-q" optional arg. */
        {
        quiet = 1; /* Used as a boolean value. */
        }
    }
    for (i = 1; i < argc; i++) /* Cycle through command line input again */
    {
        /* Create a linked list of numbers in the input */
        if (strcmp(argv[i], "-q") != 0)
        {
            /* If the read argument is a number */
            /* Create a new node */
            temp = (node *)malloc(sizeof(node));
            /* Check for malloc failure. */
            if (temp == NULL)  /* malloc failed */
            {
                fprintf(stderr, "Error: malloc() failed.\n");
                exit(1);  /* Give up, abort program. */
            }
            /* Initialize the new node */
            temp->data = atoi(argv[i]);
            temp->next = input;
            input = temp;
        }
    }
    /* Check if there are command line arguments but none that represent
     * numbers to be sorted */
    if (input == NULL)
    {
        usage(argv[0]);
        exit(1);
    }
    /* Run Quicksort on input */
    if (quiet == 1) /* If [-q] was specified */
    {
        finalsort = quicksort(input);
        free_list(input);
        free_list(finalsort);
    }
    else
    {
        finalsort = quicksort(input);
        print_list(finalsort);
        free_list(input);
        free_list(finalsort);
    }
    print_memory_leaks();
    return 0;
}
