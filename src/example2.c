#include "example2.h"
//stdlib.h already included in hsg.h

#define coord struct Coordinate

HS_INIT(coord)

//Not really a hash, just something to test it out.
size_t HS_coord_hash(Coordinate c)
{
    return abs(c.x) + abs(c.y) + abs(c.z);
}

HSResult HS_coord_eq(Coordinate a, Coordinate b)
{
    if (a.x != b.x || a.y != b.y || a.z != b.z)
    {
        return HS_FALSE;
    }
    return HS_TRUE;
}

void example_2(void)
{
    Coordinate c1 = { .x = -14, .y = 12, .z = 2 };
    Coordinate c2 = { .x = 1, .y = 1, .z = 0 };
    Coordinate c3 = { .x = 9, .y = 4, .z = 3 };
    HS_coord *hs = hs_coord_init();
    hs_coord_add(hs, c1);
    hs_coord_add(hs, c2);
    hs_coord_add(hs, c3);
    hs_coord_free(hs);
}
