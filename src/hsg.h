/*
 * Copyright 2025 Benjamin Fryxell
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef HSG_H
#define HSG_H

// #define HSG_DEBUG    //For debug printing.

#include <stdbool.h>
#include <stdlib.h>

#ifdef HSG_DEBUG
    #include <stdarg.h>
    #include <stdio.h>
#endif

#define HS_INITIAL_LENGTH    4096

typedef enum HSResult
{
   HS_SUCCESS = 0,
   HS_FALSE   = 0,
   HS_TRUE,
   HS_MEMORY_ERR,
   HS_NONMEMBER_ERR,
   HS_NULL_REFERENCE_ERR,
   HS_CAPACITY_ERR,
   HS_INIT_ERR,
   HS_OVERFLOW_ERR,
    #ifdef HSG_DEBUG
   HS_DEBUG_PRINT_ERR
    #endif
} HSResult;

//Similar TODO items as HSI (https://github.com/cello-ben/HSI/blob/main/src/hsi.h).

static HSResult _hs_debug_printf(const char *fmt, ...)
{
    #ifdef HSG_DEBUG //TODO figure out if null checks are necessary.
        if (fmt == NULL)
        {
            return(HS_NULL_REFERENCE_ERR);
        }
        va_list args;
        va_start(args, fmt);
        int vprintf_res = vprintf(fmt, args);
        va_end(args);
        if (vprintf_res < 0)      //vprintf returns a negative number if there is an error (positive error codes won't exist, since it returns the number of characters written, not including null terminator).
        {
            return(HS_DEBUG_PRINT_ERR);
        }
        return(HS_SUCCESS);
    #endif
   return(HS_SUCCESS); //TODO figure out whether or not to return from the enum here, as opposed to just 0, since we're not actually doing any operations besides returning.
}

//TODO bucket contents printing function.

#define HS_INIT(type)                                                                     \
        typedef struct ChainNode_ ## type {                                               \
           type elem;                                                                     \
           struct ChainNode_ ## type *next;                                               \
        } ChainNode_ ## type;                                                             \
                                                                                          \
        typedef struct HS_ ## type {                                                      \
           size_t capacity;                                                               \
           struct ChainNode_ ## type **nodes;                                             \
        } HS_ ## type;                                                                    \
                                                                                          \
        static struct HS_ ## type *hs_ ## type ## _init(void)                             \
        {                                                                                 \
           struct HS_ ## type *set = malloc(sizeof(struct HS_ ## type));                  \
           if (set == NULL)                                                               \
           {                                                                              \
              return(NULL);                                                               \
           }                                                                              \
           set->capacity = HS_INITIAL_LENGTH;                                             \
           set->nodes    = malloc(sizeof(struct ChainNode_ ## type) * HS_INITIAL_LENGTH); \
           if (set->nodes == NULL)                                                        \
           {                                                                              \
              free(set);                                                                  \
              return(NULL);                                                               \
           }                                                                              \
           for (size_t i = 0; i < set->capacity; i++)                                     \
           {                                                                              \
              set->nodes[i] = NULL;                                                       \
           }                                                                              \
           return(set);                                                                   \
        }                                                                                 \
                                                                                          \
        static HSResult hs_ ## type ## _free(struct HS_ ## type *set)                     \
        {                                                                                 \
           if (set == NULL)                                                               \
           {                                                                              \
              return(HS_NULL_REFERENCE_ERR);                                              \
           }                                                                              \
           if (set->nodes == NULL)                                                        \
           {                                                                              \
              free(set);                                                                  \
              return(HS_SUCCESS);                                                         \
           }                                                                              \
           for (size_t i = 0; i < set->capacity; i++)                                     \
           {                                                                              \
              struct ChainNode_ ## type *tmp;                                             \
              while (set->nodes[i] != NULL)                                               \
              {                                                                           \
                 tmp = set->nodes[i]->next;                                               \
                 free(set->nodes[i]);                                                     \
                 set->nodes[i] = tmp;                                                     \
              }                                                                           \
              free(set->nodes[i]);                                                        \
           }                                                                              \
           free(set->nodes);                                                              \
           free(set);                                                                     \
           return(HS_SUCCESS);                                                            \
        }                                                                                 \
                                                                                          \
        static HSResult hs_ ## type ## _add(struct HS_ ## type *set, type elem)           \
        {                                                                                 \
           if (set == NULL || set->nodes == NULL)                                         \
           {                                                                              \
              return(HS_NULL_REFERENCE_ERR);                                              \
           }                                                                              \
           size_t idx = HS_ ## type ## _hash(elem);                                       \
           if (set->capacity <= 0 || idx >= set->capacity)                                \
           {                                                                              \
              return(HS_CAPACITY_ERR);                                                    \
           }                                                                              \
           struct ChainNode_ ## type *node = malloc(sizeof(struct ChainNode_ ## type));   \
           if (node == NULL)                                                              \
           {                                                                              \
              return(HS_MEMORY_ERR);                                                      \
           }                                                                              \
           node->elem      = elem;                                                        \
           node->next      = set->nodes[idx];                                             \
           set->nodes[idx] = node;                                                        \
           return(HS_SUCCESS);                                                            \
        }                                                                                 \
                                                                                          \
        static HSResult hs_ ## type ## _contains(struct HS_ ## type *set, type elem)      \
        {                                                                                 \
           if (set == NULL || set->nodes == NULL)                                         \
           {                                                                              \
              return(HS_NULL_REFERENCE_ERR);                                              \
           }                                                                              \
           size_t idx = HS_ ## type ## _hash(elem);                                       \
           if (set->nodes[idx] == NULL)                                                   \
           {                                                                              \
              return(HS_FALSE);                                                           \
           }                                                                              \
           struct ChainNode_ ## type *node = set->nodes[idx];                             \
           while (node != NULL)                                                           \
           {                                                                              \
              if (HS_ ## type ## _eq(node->elem, elem))                                   \
              {                                                                           \
                 return(HS_TRUE);                                                         \
              }                                                                           \
              if (node->next != NULL)                                                     \
              {                                                                           \
                 node = node->next;                                                       \
              }                                                                           \
              else                                                                        \
              {                                                                           \
                 break;                                                                   \
              }                                                                           \
           }                                                                              \
           return(HS_FALSE);                                                              \
        }                                                                                 \
                                                                                          \
        static HSResult hs_ ## type ## _delete(struct HS_ ## type *set, type elem)        \
        {                                                                                 \
           size_t idx = HS_ ## type ## _hash(elem);                                       \
           struct ChainNode_ ## type *tmp, *prev;                                         \
           tmp  = set->nodes[idx];                                                        \
           prev = NULL;                                                                   \
           while (tmp)                                                                    \
           {                                                                              \
              if (HS_ ## type ## _eq(tmp->elem, elem))                                    \
              {                                                                           \
                 if (prev != NULL)                                                        \
                 {                                                                        \
                    prev->next = tmp->next;                                               \
                    free(tmp);                                                            \
                    return(HS_SUCCESS);                                                   \
                 }                                                                        \
                 else                                                                     \
                 {                                                                        \
                    set->nodes[idx] = set->nodes[idx]->next;                              \
                    free(tmp);                                                            \
                    return(HS_SUCCESS);                                                   \
                 }                                                                        \
              }                                                                           \
              prev = tmp;                                                                 \
              tmp  = tmp->next;                                                           \
           }                                                                              \
           return(HS_NONMEMBER_ERR);                                                      \
        }

#endif //HSG_H
