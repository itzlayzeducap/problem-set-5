#ifndef DICTIONARY
#define DICTIONARY

#include <stdbool.h>
#define MAX_LENGTH 45

bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif