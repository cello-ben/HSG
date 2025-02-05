#ifndef EXAMPLE_2_H
#define EXAMPLE_2_H

#include <stddef.h>
#include "hsg.h"

typedef struct Coordinate {
    int x;
    int y;
    int z;
} Coordinate;

HSResult HS_coord_eq(Coordinate a, Coordinate b);
size_t HS_coord_hash(Coordinate c);
void example_2(void);

#endif //EXAMPLE_2_H
