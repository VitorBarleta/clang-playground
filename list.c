#include <stdlib.h>
#include "types.c"
#include "list.h"

u8_t _resize(list_t *list)
{
    size_t new_cap = list->_size * list->capacity * 2;
    void *r_items = realloc(list->items, new_cap);

    if (r_items != NULL)
    {
        list->items = r_items;
        list->capacity = new_cap / list->_size;
        return 1;
    }

    void *new = malloc(new_cap);

    if (new == NULL)
    {
        return 0;
    }

    for (uint_t i = 0; i < list->capacity; i++)
    {
        void *pt = new + (i * list->_size);
        pt = list->items + (i * list->_size);
    }

    free(list->items);
    list->items = new;
    list->capacity = new_cap / list->_size;

    return 0;
}

void *_ladd(list_t *list, size_t size)
{
    if (size != list->_size)
    {
        return NULL;
    }

    if (list->count >= list->capacity)
    {
        u8_t success = _resize(list);
        if (!success)
        {
            return NULL;
        }
    }

    void *i = list->items + (list->count * list->_size);
    list->count++;
    return i;
}

list_t *lnew(uint_t capacity, size_t size)
{
    list_t *list = malloc(sizeof(list_t));
    list->_size = size;
    list->capacity = capacity;
    list->count = 0;
    list->items = malloc(size * capacity);
    return list;
}

void lfree(list_t *list)
{
    void *a = list->items;
    list->items = NULL;

    free(a);
    free(list);
}

void *lget(list_t *list, uint_t index)
{
    return list->items + (index * list->_size);
}

u8_t laddi(list_t *list, int value)
{
    int *item = (int *)_ladd(list, sizeof(int));
    if (item == NULL)
    {
        list->count--;
        return 0;
    }

    *item = value;
    return 1;
}