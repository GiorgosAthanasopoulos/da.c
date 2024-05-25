#include "da_int.h"

int da_get_i(DA *da, int index)
{
    return (int)(int *)da_get(da, index);
}

int da_front_i(DA *da)
{
    return (int)(int *)da_front(da);
}

int da_back_i(DA *da)
{
    return (int)(int *)da_back(da);
}

int *da_data_i(DA *da)
{
    return (int *)da_data(da);
}

void da_append_i(DA *da, int item)
{
    da_append(da, (void *)item);
}

void da_insert_i(DA *da, int index, int item)
{
    da_insert(da, index, (void *)item);
}

int da_pop_i(DA *da)
{
    return (int)(int *)da_pop(da);
}

int da_remove_i(DA *da, int index)
{
    return (int)(int *)da_remove(da, index);
}
