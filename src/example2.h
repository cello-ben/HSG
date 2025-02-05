#ifndef HS_EXAMPLE_2
#define HS_EXAMPLE_2

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

#endif //HS_EXAMPLE_2
