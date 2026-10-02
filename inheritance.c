#include <stdbool.h>
#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "inheritance.h"

person *create_family(int generations)
{
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        return NULL;
    }
    
    if (generations > 1)
    {
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);
        
        if (p->parents[0] == NULL || p->parents[1] == NULL)
        {
            free_family(p->parents[0]);
            free_family(p->parents[1]);
            free(p);
            return NULL;
        }
        
        p->roads[0] = p->parents[0]->roads[rand() % 2];
        p->roads[1] = p->parents[1]->roads[rand() % 2];
    }
    else
    {
        p->parents[0] = NULL;
        p->parents[1] = NULL;
        p->roads[0] = gen_road();
        p->roads[1] = gen_road();
    }
    
    return p;
}

void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }
    
    free_family(p->parents[0]);
    free_family(p->parents[1]);
    
    free(p);
}

void print_family(person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }
    
    printf("%*s", generation * 4, "");
    
    if (generation == 0)
    {
        printf("child (gen %i): blood type %c%c\n", generation, p->roads[0], p->roads[1]);
    }
    else if (generation == 1)
    {
        printf("parent (gen %i): blood type %c%c\n", generation, p->roads[0], p->roads[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("great-");
        }
        printf("grandparent (gen %i): blood type %c%c\n", generation, p->roads[0], p->roads[1]);
    }
    
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

char gen_road(void)
{
    const char roads[] = {'A', 'B', 'O'};
    return roads[rand() % 3];
}

int main(void)
{
    srand(time(0));

    person *p = create_family(GENERATIONS);
    if (p == NULL)
    {
        printf("failed to create family\n");
        return 1;
    }

    print_family(p, 0);
    free_family(p);

    return 0;
}