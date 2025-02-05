#include <stdio.h>
#include <stdlib.h>
#include "example1.h"
#include "example2.h"
#include "example3.h"

#define NUM_EXAMPLES 3

int usage(void)
{
    return printf("Usage: ./hsg <example_number>\n");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        return usage();
    }
    int example = atoi(argv[1]);
    if (example <= 0 || example > NUM_EXAMPLES)
    {
        return usage();
    }
    switch (example)
    {
        case 1:
            example_1();
            break;
        case 2:
            example_2();
            break;
        case 3:
            example_3();
            break;
        default:
            break;
    }
    return 0;
}
