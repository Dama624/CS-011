/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s)
{
    int total; /* Sum of character int values */
    int value; /* Integer in range of [0, NSLOTS - 1] */
    total = 0;
    /* Loop for as long as the next character is not empty */
    while(*s != '\0')
    {
        total += *s;
        s++;
    }
    value = total % NSLOTS;
    return value;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    /* Allocate memory for the node "result" */
    node *result = (node *)malloc(sizeof(node));
    /* Check if malloc fails */
    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }
    result->key = (char *)malloc((strlen(key) + 1) * sizeof(char));
    if (result->key == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }
    /* Fill in the new node with the given values. */
    strcpy(result->key, key);
    result->value = value;
    result->next = NULL;
    return result;
}

/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *n;     /* a single node of the list */
    while (list != NULL)
    {
        n = list;
        list = list->next;
        free(n->key);
        free(n);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    int i;
    /* Allocate memory for the table "result" */
    hash_table *result = (hash_table *)malloc(sizeof(hash_table));
    /* Check if malloc fails */
    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }
    result->slot = (node **)malloc(NSLOTS * sizeof(node *));
    /* Check if malloc fails */
    if (result->slot == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }
    /* Fill the new table with an empty list */
    for (i = 0; i < NSLOTS; i++)
    {
        result->slot[i] = NULL;
    }
    return result;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i;
    /* Loop through the slots */
    for (i = 0; i < NSLOTS; i++)
    {
        /* Free the list in a slot */
        free_list(ht->slot[i]);
    }
    free(ht->slot);
    free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    int hvalue; /* The hash value for the given key */
    node *temp; /* A temp node of a linked list in a hash table slot */
    hvalue = hash(key);
    /* If no linked list exists at this hash value array location */
    if (ht->slot[hvalue] == NULL)
    {
        return 0;
    }
    /* If a linked list exists at this location */
    else
    {
        /* Loop through the linked list */
        for (temp = ht->slot[hvalue]; temp != NULL; temp = temp->next)
        {
            /* If the key is found in this node */
            if (strcmp(temp->key, key) == 0)
            {
                return temp->value;
            }
        }
        /* A key is not found in the list */
        return 0;
    }
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
    int hvalue; /* The hash value for the given key */
    node *temp; /* A temp node of a linked list in a hash table slot */
    int found; /* A boolean for if a key is found in a linked list */
    found = 0;
    hvalue = hash(key);
    /* If no linked list exists at this hash value array location */
    if (ht->slot[hvalue] == NULL)
    {
        ht->slot[hvalue] = create_node(key, value);
    }
    /* If a linked list exists at this location */
    else
    {
        /* Loop through the linked list */
        for (temp = ht->slot[hvalue]; temp != NULL; temp = temp->next)
        {
            /* If the key is found in this node */
            if (strcmp(temp->key, key) == 0)
            {
                found = 1;
                temp->value = value;
            }
        }
        /* If the key is not found in this slot */
        if (found == 0)
        {
            /* Add new node here */
            temp = create_node(key, value);
            temp->next = ht->slot[hvalue];
            ht->slot[hvalue] = temp;
        }
    }
    free(key);
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    int i;
    node *tempn; /* A temp node of a linked list in a hash table slot */
    /* Loop through the slots of the hash table */
    for (i = 0; i < NSLOTS; i++)
    {
        /* Loop through the linked list of the slot */
        for (tempn = ht->slot[i]; tempn != NULL; tempn = tempn->next)
        {
            printf("%s ", tempn->key);
            printf("%d\n", tempn->value);
        }
    }
}


