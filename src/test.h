#include <stddef.h>
#include "hsg.h"

typedef struct StringQuartet {
    char *group_name;
    char *violin_1;
    char *violin_2;
    char *viola;
    char *cello;
} StringQuartet;

typedef StringQuartet* StringQuartetPtr;

HSResult HS_int_eq(int a, int b);
HSResult HS_StringQuartetPtr_eq(StringQuartet *a, StringQuartet *b);
size_t HS_int_hash(int num);
size_t HS_StringQuartetPtr_hash(StringQuartet *quartet);

void test(void);
