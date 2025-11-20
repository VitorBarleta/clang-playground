#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#include "types.c"

typedef struct
{
    uint_t capacity;
    uint_t count;
    size_t _size;
    void *items;
} list_t;

list_t *lnew(uint_t capacity, size_t size);
void lfree(list_t *list);
void *lget(list_t *list, uint_t index);
u8_t laddi(list_t *list, int value);
#endif