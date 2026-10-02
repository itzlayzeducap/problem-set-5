#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define TABLE_SIZE 1000000

typedef struct node
{
    char word[MAX_LENGTH + 1];
    struct node *next;
} node;

static node *table[TABLE_SIZE];
static unsigned int word_count = 0;

unsigned int hash(const char *word)
{
    unsigned long h = 5381;
    int c;

    while ((c = (unsigned char) *word++))
    {
        h = ((h << 5) + h) + tolower(c);
    }

    return h % TABLE_SIZE;
}

unsigned int size(void)
{
    return word_count;
}

bool check(const char *word)
{
    node *current = table[hash(word)];

    while (current != NULL)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }
        current = current->next;
    }

    return false;
}

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[MAX_LENGTH + 1];

    while (fscanf(file, "%45s", word) == 1)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            unload();
            
            return false;
        }

        strcpy(n->word, word);

        unsigned int index = hash(word);

        n->next = table[index];
        table[index] = n;

        word_count++;
    }

    fclose(file);
    return true;
}

bool unload(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        node *current = table[i];

        while (current != NULL)
        {
            node *tmp = current;
            current = current->next;
            free(tmp);
        }

        table[i] = NULL;
    }

    word_count = 0;
    return true;
}

int main(void) {
    if (!load("small")) {
        printf("failed to load large dictionary");
        return 1;
    }

    printf("words: %d\n", size());
    
    printf("cat: %u\n", check("cat"));
    printf("catatata: %u\n", check("catatata"));
    printf("hello: %u\n", check("hello"));
    printf("gav: %u\n", check("gav"));    

    if (!unload()) {
        printf("failed to unload");
        return 1;
    }

    return 0;
}