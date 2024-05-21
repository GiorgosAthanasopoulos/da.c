#include <stdio.h>
#include <stdlib.h>

#include "da.h"

DA *da_init_cap(DA_Type type, int new_capacity)
{
    DA *da = malloc(sizeof(DA));

    if (!da)
    {
        return NULL;
    }

    if (new_capacity <= 0)
    {
        new_capacity = DA_DEFAULT_CAPACITY;
    }

    da->size = 0;
    da->capacity = new_capacity;
    da->type = type;
    da->data = NULL;

    da_data_malloc(da);
    if (!da->data)
    {
        if (da)
        {
            free(da);
            da = NULL;
        }
        return NULL;
    }

    return da;
}

DA *da_init(DA_Type type)
{
    return da_init_cap(type, DA_DEFAULT_CAPACITY);
}

void da_data_malloc(DA *da)
{
    if (!da)
    {
        return;
    }

    switch (da->type)
    {
    case INT:
        da->data = malloc(sizeof(int) * da->capacity);
    }
}

void da_extend_cap(DA *da, int by_capacity)
{
    if (!da)
    {
        return;
    }

    if (by_capacity <= 0)
    {
        return;
    }

    da->capacity += by_capacity;
    void *data_backup = da->data;

    da_data_malloc(da);
    if (!da->data)
    {
        return;
    }

    da->data = data_backup;
}

void da_extend(DA *da)
{
    da_extend_cap(da, DA_DEFAULT_CAPACITY);
}

void *da_get(DA *da, int index)
{
    if (!da)
    {
        return NULL;
    }
    if (!da->data)
    {
        return NULL;
    }
    if (index < 0 || index > da->size - 1)
    {
        return NULL;
    }
    return da->data[index];
}

void *da_front(DA *da)
{
    return da_get(da, 0);
}

void *da_back(DA *da)
{
    return da_get(da, da->size - 1);
}

void **da_data(DA *da)
{
    if (!da)
    {
        return NULL;
    }
    return da->data;
}

int da_empty(DA *da)
{
    if (!da)
    {
        return 1;
    }
    return da->size == 0;
}

int da_size(DA *da)
{
    if (!da)
    {
        return 0;
    }
    return da->size;
}

void da_reserve(DA *da, int capacity)
{
    da_extend_cap(da, capacity);
}

int da_capacity(DA *da)
{
    if (!da)
    {
        return 0;
    }
    return da->capacity;
}

void da_shrink_to_fit(DA *da)
{
    if (!da)
    {
        return;
    }

    da_resize(da, da->size);
}

void da_resize(DA *da, int new_capacity)
{
    if (!da)
    {
        return;
    }

    if (new_capacity < da->size)
    {
        return;
    }

    da->capacity = new_capacity;
    void **data_backup = da->data;
    da_data_malloc(da);
    da->data = data_backup;
}

void da_swap(DA *da, DA *other)
{
    if (!da)
    {
        return;
    }
    if (!other)
    {
        return;
    }

    int tmp_capacity = da->capacity;
    void **tmp_data = da->data;
    da->capacity = other->capacity;
    da->data = other->data;
    other->capacity = tmp_capacity;
    other->data = tmp_data;
}

void da_append(DA *da, void *item)
{
    if (!da)
    {
        return;
    }

    if (!da->data)
    {
        da_data_malloc(da);
        if (!da->data)
        {
            return;
        }
    }

    if (da->size == da->capacity)
    {
        da_extend(da);

        if (!da->data)
        {
            return;
        }
    }

    switch (da->type)
    {
    case INT:
        int **data = (int **)da->data;
        data[da->size++] = (int *)item;
        // da->data[da->size++] = (int *)item;
    }
}

void da_insert(DA *da, int index, void *item)
{
    if (!da)
    {
        return;
    }

    if (index < 0 || index > da->size)
    {
        return;
    }

    // TODO: implement insert
}

void *da_pop(DA *da)
{
    if (!da)
    {
        return NULL;
    }
    if (!da->data)
    {
        return NULL;
    }

    void *res = da->data[da->size - 1];
    da->size--;
    return res;
}

void *da_remove(DA *da, int index)
{
    if (!da)
    {
        return NULL;
    }
    if (!da->data)
    {
        return NULL;
    }

    if (index < 0 || index > da->size)
    {
        return NULL;
    }

    // TODO: implement remove
}

void da_clear(DA *da)
{
    if (!da)
    {
        return;
    }
    da->size = 0;
}

void da_clear_free(DA *da)
{
    if (!da)
    {
        return;
    }
    if (!da->data)
    {
        return;
    }
    da_clear(da);
    da_data_free(da);
    da_resize(da, DA_DEFAULT_CAPACITY);
}

void da_clear_shrink_cap(DA *da, int new_capacity)
{
    if (!da)
    {
        return;
    }

    if (new_capacity < 0)
    {
        return;
    }
    if (new_capacity == 0)
    {
        da_clear(da);
        da_resize(da, DA_DEFAULT_CAPACITY);
        return;
    }

    da->capacity = new_capacity;
    if (da->data)
    {
        free(da->data);
        da->data = NULL;
    }
    da_data_malloc(da);
}

void da_clear_shrink(DA *da)
{
    da_clear_shrink_cap(da, DA_DEFAULT_CAPACITY);
}

void da_debug_print(DA *da)
{
    if (!da)
    {
        return;
    }
    if (!da->data)
    {
        return;
    }

    switch (da->type)
    {
    case INT:
        for (int i = 0; i < da->size; ++i)
        {
            printf("%d ", (int *)da_get(da, i));
        }
    }
}

void da_debug_print_elem(DA *da, int index)
{
    if (!da)
    {
        return;
    }
    if (!da->data)
    {
        return;
    }

    switch (da->type)
    {
    case INT:
        printf("%d", (int *)da_get(da, index));
    }
}

void da_data_free(DA *da)
{
    if (!da)
    {
        return;
    }
    if (!da->data)
    {
        return;
    }
    free(da->data);
    da->data = NULL;
}

void da_free(DA **da)
{
    if (!da)
    {
        return;
    }
    if (!*da)
    {
        return;
    }

    if ((*da)->data)
    {
        free((*da)->data);
        (*da)->data = NULL;
    }
    free(*da);
    *da = NULL;
}
