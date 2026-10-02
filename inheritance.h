#ifndef INHERITANCE
#define INHERITANCE

const int GENERATIONS = 4;

typedef struct person
{
    struct person *parents[2];
    char roads[2];
} person;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char gen_road(void);

#endif