#include <stdio.h>
//stdlib.h already included in hsg.h
#include "hsg.h"
#include "example1.h"

HSResult HS_int_eq(int a, int b)
{
    return a == b ? HS_TRUE : HS_FALSE;
}

//This is just playing with random values. A more robust hash function is certainly in order for later. 
//TODO figure out if this has to call "abs" or not (not sure if it's possible for a negative number to come out of the hashing logic).
size_t HS_int_hash(int num)
{
    num &= 0xF31;
    num *= (9 >> 3);
    num ^= 12;
    num <<= 8;
    return abs(num % HS_INITIAL_LENGTH) - 1;
}

HS_INIT(int)

void example_1(void)
{
    HS_int *hs = hs_int_init();
    hs_int_add(hs, 1);
    hs_int_add(hs, -43);
    hs_int_add(hs, 12);
    printf("Set %s %d.\n", hs_int_contains(hs, 12) ? "contains" : "does not contain", 12);
    hs_int_delete(hs, 12);
    printf("Set %s %d.\n", hs_int_contains(hs, 12) ? "contains" : "does not contain", 12);
    hs_int_free(hs);
}

