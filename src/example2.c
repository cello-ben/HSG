#include <stdio.h>
//stdlib.h already included in hsg.h
#include "hsg.h"
#include "example2.h"

//Not really a hash, just something to test it out.
size_t HS_Coordinate_hash(Coordinate c)
{
    return abs(c.x) + abs(c.y) + abs(c.z);
}

HSResult HS_Coordinate_eq(Coordinate a, Coordinate b)
{
    if (a.x != b.x || a.y != b.y || a.z != b.z)
    {
        return HS_FALSE;
    }
    return HS_TRUE;
}

HS_INIT(Coordinate)

void example_2(void)
{
    Coordinate c1 = { .x = -14, .y = 12, .z = 2 };
    Coordinate c2 = { .x = 1, .y = 1, .z = 0 };
    Coordinate c3 = { .x = 9, .y = 4, .z = 3 };
    HS_Coordinate *hs = hs_Coordinate_init();
    hs_Coordinate_add(hs, c1);
    hs_Coordinate_add(hs, c2);
    hs_Coordinate_add(hs, c3);
    printf("Set %s c2.\n", hs_Coordinate_contains(hs, c2) ? "contains" : "does not contain");
    hs_Coordinate_delete(hs, c2);
    printf("Set %s c2.\n", hs_Coordinate_contains(hs, c2) ? "contains" : "does not contain");
    hs_Coordinate_free(hs);
}
