// Implements a dictionary's functionality
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table () 178873
const unsigned int N = 78919;

// Hash table
node *table[N];

// assign and declare head pointer
node *head;

// Number of words in dictionary
int dictionarywords = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // runs word through hash function
    node *cursor = table[hash(word)];

    // search linked list for word
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }

        else
        {
            cursor = cursor -> next;
        }
    }
    return false;
}

// Hashes word to a number. Based on sdbm hash function from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long index, hash = 65599;
    int c;

    while ((c = *word++) != 0) // (int c = 0; word[c] != '/0'; c++)
    {
        hash = tolower(c) + (hash << 6) + (hash << 16) - hash;
    }

    hash %= N;
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Couldn't load dictionary\n");
        return false;
    }

    // allocate memory for buffer array in which to read each dictionary word
    char *wordbuffer = malloc(sizeof(char) * LENGTH + 1);
    if (wordbuffer == NULL)
    {
        printf("Couldn't create buffer.\n");
        return false;
    }

    // read each word, create node, store in hash table
    while (fscanf(dict, "%s", wordbuffer) != EOF)
    {
        // allocate memory for and create new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Couldn't create node.\n");
            return false;
        }

        strcpy(n -> word, wordbuffer);
        n -> next = NULL;

        // increase word counter
        dictionarywords++;

        // run word through hash function
        long index = hash(n -> word);

        // insert new node
        n -> next = table[index];
        table[index] = n;

    }

    // close dictionary file
    fclose(dict);

    // free wordbuffer
    free(wordbuffer);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarywords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // frees each node in hash table
    for (int i = 0; i < N; i++)
    {
        if (table[i] != 0)
        {
            node *cursor = table[i];
            node *tmp = cursor;

            while (tmp != NULL)
            {
                cursor = cursor -> next;
                free(tmp);
                tmp = cursor;
            }
        }
    }

    return true;
}
