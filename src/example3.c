#include <stdio.h>
//stdlib.h already included in hsg.h
#include "hsg.h"
#include "example3.h"

//In order to use a pointer, we need to do a typedef, which you can see in the header file.

HSResult HS_Person_ptr_eq(Person *a, Person *b)
{
    return a == b ? HS_TRUE : HS_FALSE;
}

//This is just playing with random values. A more robust hash function is certainly in order for later. 
//TODO figure out if this has to call "abs" or not (not sure if it's possible for a negative number to come out of the hashing logic).
size_t HS_Person_ptr_hash(Person *p)
{
    int n = p->age;
    n &= 0xF31;
    n *= (9 >> 3);
    n ^= 12;
    n <<= 8;
    return abs(n % HS_INITIAL_LENGTH) - 1;
}

HS_INIT(Person_ptr)

void example_3(void)
{
    HS_Person_ptr *hs = hs_Person_ptr_init();
    Person *a = malloc(sizeof(Person));
    a->age = 24;
    a->name = "Johnny";
    Person *b = malloc(sizeof(Person));
    b->age = 47;
    b->name = "Jean";
    hs_Person_ptr_add(hs, a);
    hs_Person_ptr_add(hs, b);
    printf("Set %s %s.\n", hs_Person_ptr_contains(hs, a) ? "contains" : "does not contain", a->name);
    hs_Person_ptr_delete(hs, a);
    printf("Set %s %s\n", hs_Person_ptr_contains(hs, a) ? "contains" : "does not contain", a->name);
    hs_Person_ptr_free(hs);
    free(a); //TODO figure out if these are needed.
    free(b); 
}

