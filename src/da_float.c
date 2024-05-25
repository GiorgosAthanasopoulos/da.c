#include <stdlib.h>

#include "da_float.h"

float da_get_f(DA *da, int index)
{
    return *(float *)da_get(da, index);
}

float da_front_f(DA *da)
{
    return *(float *)da_front(da);
}

float da_back_f(DA *da)
{
    return *(float *)da_back(da);
}

float *da_data_f(DA *da)
{
    return (float *)da_data(da);
}

void da_append_f(DA *da, float item)
{
    // FIXME: fix memory leak
    float *item_p = malloc(sizeof(float));
    *item_p = item;
    da_append(da, (void *)item_p);
}

void da_insert_f(DA *da, int index, float item)
{
    // FIXME: fix memory leak
    float *item_p = malloc(sizeof(float));
    *item_p = item;
    da_insert(da, index, (void *)item_p);
}

float da_pop_f(DA *da)
{
    return *(float *)da_pop(da);
}

float da_remove_f(DA *da, int index)
{
    return *(float *)da_remove(da, index);
}
