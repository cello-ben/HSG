#ifndef EXAMPLE_3_H
#define EXAMPLE_3_H

#include <stddef.h>
#include "hsg.h"

typedef struct Person {
    int age;
    char *name;
} Person;


typedef Person* Person_ptr;

HSResult HS_Person_ptr_eq(Person *a, Person *b);
size_t HS_Person_ptr_hash(Person *p);
void example_3(void);

#endif //EXAMPLE_3_H
