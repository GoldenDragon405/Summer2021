// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
int words;
// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];
bool check(const char *word)
{
    int hashValue = hash(word);
    if (table[hashValue] == NULL)
    {
        return false;
    }
    else
    {
        for (node *tmp = table[hashValue]; tmp != NULL; tmp = tmp -> next)
        {
            if (strcasecmp(tmp -> word, word) == 0)
            {
                return true;
            }
            else
            {
                continue;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    long sumoL = 0; // initializing sum
    for (int i = 0; i < strlen(word); i++)
    {
        sumoL += tolower(word[i]); //adds the ascii values of all the letters
    }
    return sumoL % N; //makes sure the sum is not greater than 100000
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dictionary == NULL) //opens the dictionary file
    {
        return false;
    }
    char word1[LENGTH + 1];
    while (fscanf(dict, "%s", word1) != EOF)
    {
        node *n = malloc(sizeof(node)); // mallocs the size of a node
        if (n == NULL)
        {
            return false;
        }
        n -> next = NULL;
        // printf("%p\n", n -> next);
        strcpy(n->word, word1);
        int hashValue = hash(word1); //creates a linked list -- prints for testing
        if (table[hashValue] == NULL)
        {
            table[hashValue] = n;
            //printf("%p\n", *&n);
        }
        else
        {
            n -> next = table[hashValue];
            table[hashValue] = n;
            //printf("%p\n", *&n->next->next);
            //printf("%p\n", *&n->next);
            //printf("%p\n", n -> next -> next);


        }
        words++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words; //just returns # of words
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp = malloc(sizeof(node));
    node *other = malloc(sizeof(node));
    other -> next = tmp;
    int counter = 0;
    for (int i = 97; i < N; i++) //starts at the first possible value
    {
        tmp = table[i];
        while (tmp != NULL && table[i] != NULL)
        {
            node *n = table[i];
            n = tmp;
            tmp = tmp -> next; //cleans up the linked list
            free(n);
            counter++;
        }

    }
    free(other -> next); //frees tmp and other
    free(other);
    if (counter == words)
    {
        return true;
    }
    else
    {
        return false;
    }
}
