#include <assert.h>
#include <string.h>
#include "test.h"

HS_INIT(int)
HS_INIT(StringQuartetPtr)

#define INT_ITER 10000
#define SQ_ITER 3000

//This is just playing with random values. A more robust hash function is certainly in order for later. 
//TODO figure out if this has to call "abs" or not (not sure if it's possible for a negative number to come out of the hashing logic).
//TODO figure out how to avoid collision with other declaration.
// size_t HS_int_hash(int num)
// {
//     num &= 0xF31;
//     num *= (9 << 3);
//     num ^= 12;
//     num <<= 8;
//     return abs(num % HS_INITIAL_LENGTH) - 1;
// }

size_t HS_StringQuartetPtr_hash(StringQuartet *quartet)
{
    long num = 0xFFFFFFFB; //Big prime number
    size_t len = strlen(quartet->group_name);
    for (size_t i = 0; i < len; i++)
    {
        switch(i % 4)
        {
            case 0:
                num *= (quartet->group_name[i] << 7);
                break;
            case 1:
                num ^= (quartet->group_name[i]);
                break;
            case 2:
                num <<= (quartet->group_name[i]);
                break;
            case 3:
                num *= (quartet->group_name[i]);
                break;
            default:
                break;
        }
    }
    for (size_t i = 0; i < len; i++)
    {
        switch(i % 4)
        {
            case 0:
                num *= (quartet->violin_1[i] << 7);
                break;
            case 1:
                num ^= (quartet->violin_1[i]);
                break;
            case 2:
                num <<= (quartet->violin_1[i]);
                break;
            case 3:
                num *= (quartet->violin_1[i]);
                break;
            default:
                break;
        }
    }
    for (size_t i = 0; i < len; i++)
    {
        switch(i % 4)
        {
            case 0:
                num *= (quartet->violin_2[i] << 7);
                break;
            case 1:
                num ^= (quartet->violin_2[i]);
                break;
            case 2:
                num <<= (quartet->violin_2[i]);
                break;
            case 3:
                num *= (quartet->violin_2[i]);
                break;
            default:
                break;
        }
    }
    for (size_t i = 0; i < len; i++)
    {
        switch(i % 4)
        {
            case 0:
                num *= (quartet->viola[i] << 7);
                break;
            case 1:
                num ^= (quartet->viola[i]);
                break;
            case 2:
                num <<= (quartet->viola[i]);
                break;
            case 3:
                num *= (quartet->viola[i]);
                break;
            default:
                break;
        }
    }
    for (size_t i = 0; i < len; i++)
    {
        switch(i % 4)
        {
            case 0:
                num *= (quartet->cello[i] << 7);
                break;
            case 1:
                num ^= (quartet->cello[i]);
                break;
            case 2:
                num <<= (quartet->cello[i]);
                break;
            case 3:
                num *= (quartet->cello[i]);
                break;
            default:
                break;
        }
    }
    return (int)num;
}

void test(void)
{
    HS_int *hs_int = hs_int_init();
    assert(hs_int != NULL);
    for (int i = 0; i < INT_ITER; i++)
    {
        HSResult res = hs_int_add(hs_int, i);
        assert(res == HS_SUCCESS);
    }
    for (int i = 0; i < INT_ITER; i++)
    {
        assert(hs_int_contains(hs_int, i) == HS_TRUE);
    }
    for (int i = 0; i < INT_ITER; i++)
    {
        if (i % 2 == 0)
        {
            hs_int_delete(hs_int, i);
        }
    }
    for (int i = 0; i < INT_ITER; i++)
    {
        HSResult contains = hs_int_contains(hs_int, i);
        if (i % 2 == 0)
        {
            assert(contains == HS_FALSE);
        }
        else
        {
            assert(contains == HS_TRUE);
        }
    }
    hs_int_free(hs_int); //TODO figure out if there is a way to optimize freeing.

    HS_StringQuartetPtr *hs_sq = hs_StringQuartetPtr_init();
    assert(hs_sq != NULL);

    // for (int i = 0; i < )
    
    _hs_debug_printf("All tests passed!\n");
}
