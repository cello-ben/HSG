# HSG
With some very helpful guidance from some commenters on r/cprogramming, I created [HSI](https://github.com/cello-ben/HSI). One commenter recommended that I make a generic hash set, so I present HSG, a macro-based hash set that uses the same principles as HSI, but allows for user-defined types. There's a great deal of work to do on it to make it *truly* generic. However, I'm proud of how it has come out so far. **Don't use this in production, it's an educational project for me.**

# Usage
First, create a hash function for your desired type, which, at least for now, *must* follow this pattern:
```
size_t HS_<type>_hash(<type> <variable_name>)
```

Then, with `hsg.h` included, call `HS_INIT(<type>)`. This will cause the preprocessor to generate code for a hash set of your specified type, and the functions that go along with it. The struct and the functions to go along with it will look like this:
```
HS_<type> //struct
HS_<type> hs_<type>_init()
hs_<type>_add(HS_<type> set, <type> elem)
hs_<type>_delete(HS_<type> set, <type> elem)
hs_<type>_contains(HS_<type> set, <type> elem)
hs_<type>_free(HS_<type> set)
```
Here's an example of its usage, which you can build using `make`, since it's in `example.c`:
```
#include <stddef.h>
#include <stdio.h>
#include "hsg.h"

//This is just playing with random values. A more robust hash function is certainly in order for later.
size_t HS_int_hash(int num)
{
    num &= 0xF31;
    num *= (9 >> 3);
    num ^= 12;
    num <<= 8;
    return abs(num % HS_INITIAL_LENGTH) - 1;
}

HS_INIT(int)

int main(void)
{
    HS_int *hs = hs_int_init();
    hs_int_add(hs, 1);
    hs_int_add(hs, -43);
    hs_int_add(hs, 12);
    printf("Set %s %d.\n", hs_int_contains(hs, 12) ? "contains" : "does not contain", 12);
    hs_int_delete(hs, 12);
    printf("Set %s %d.\n", hs_int_contains(hs, 12) ? "contains" : "does not contain", 12);
    hs_int_free(hs);
    return 0;
}
```

See the examples in `src` for more. Thanks so much to u/strcspn on Reddit for their help with adding struct support. I have used their advice to make this considerably more versatile.