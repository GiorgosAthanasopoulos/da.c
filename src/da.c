#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "da.h"

DA *da_init_cap(DA_Type type, int new_capacity)
{
    DA *da = malloc(sizeof(DA));

    if (!da)
    {
        fprintf(stderr, "da_init_cap(%d, %d) :: failed to allocate memory for DA struct\n", type, new_capacity);
        return NULL;
    }

    if (new_capacity <= 0)
    {
        fprintf(stderr, "da_init_cap(%d, %d) :: new_capacity <= 0 : Using DA_DEFAULT_CAPACITY intead\n", type,
                new_capacity);
        new_capacity = DA_DEFAULT_CAPACITY;
    }

    da->size = 0;
    da->capacity = new_capacity;
    da->type = type;
    da->data = NULL;

    da_data_malloc(da);
    if (!da->data)
    {
        fprintf(stderr, "da_init_cap(%d, %d) :: failed to allocate memory for data\n", type, new_capacity);
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
        fprintf(stderr, "da_data_malloc(%p) :: da is NULL\n", da);
        return;
    }

    if (da->data)
    {
        // FIXME: free(): double free detected in tcache 2
        // free(da->data);
        da->data = NULL;
    }

    switch (da->type)
    {
    case INT:
        da->data = malloc(sizeof(int) * da->capacity);
        break;
    }
}

void da_extend_cap(DA *da, int by_capacity)
{
    if (!da)
    {
        fprintf(stderr, "da_extend_cap(%p, %d) :: da is NULL\n", da, by_capacity);
        return;
    }

    if (by_capacity <= 0)
    {
        fprintf(stderr, "da_extend_cap(%p, %d) :: by_capacity is <= 0\n", da, by_capacity);
        return;
    }

    da->capacity += by_capacity;
    void *data_backup = da->data;

    da_data_malloc(da);
    if (!da->data)
    {
        fprintf(stderr, "da_extend_cap(%p, %d) :: failed to allocate memory for data\n", da, by_capacity);
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
        fprintf(stderr, "da_get(%p, %d) :: da is NULL\n", da, index);
        return NULL;
    }

    if (!da->data)
    {
        fprintf(stderr, "da_get(%p, %d) :: da->data is NULL\n", da, index);
        return NULL;
    }

    if (index < 0 || index >= da->size)
    {
        fprintf(stderr, "da_get(%p, %d) :: index out of bounds\n", da, index);
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
        fprintf(stderr, "da_data(%p) :: da is NULL\n", da);
        return NULL;
    }

    return da->data;
}

int da_empty(DA *da)
{
    if (!da)
    {
        fprintf(stderr, "da_empty(%p) :: da is NULL\n", da);
        return 1;
    }

    return da->size == 0;
}

int da_size(DA *da)
{
    if (!da)
    {
        fprintf(stderr, "da_size(%p) :: da is NULL\n", da);
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
        fprintf(stderr, "da_capacity(%p) :: da is NULL\n", da);
        return 0;
    }

    return da->capacity;
}

void da_shrink_to_fit(DA *da)
{
    if (!da)
    {
        fprintf(stderr, "da_shrink_to_fit(%p) :: da is NULL\n", da);
        return;
    }

    da_resize(da, da->size);
}

void da_resize(DA *da, int new_capacity)
{
    if (!da)
    {
        fprintf(stderr, "da_resize(%p, %d) :: da is NULL\n", da, new_capacity);
        return;
    }

    if (new_capacity < da->size)
    {
        fprintf(stderr, "da_resize(%p, %d) :: index out of bounds\n", da, new_capacity);
        return;
    }

    da->capacity = new_capacity;
    void **data_backup = da->data;
    da_data_malloc(da);

    for (int i = 0; i < da->size; ++i)
    {
        da->data[i] = data_backup[i];
    }
}

void da_swap(DA *da, DA *other)
{
    if (!da)
    {
        fprintf(stderr, "da_swap(%p, %p) :: da is NULL\n", da, other);
        return;
    }
    if (!other)
    {
        fprintf(stderr, "da_swap(%p, %p) :: other is NULL\n", da, other);
        return;
    }

    int tmp_capacity = da->capacity;
    int tmp_size = da->size;
    void **tmp_data = da->data;
    da->capacity = other->capacity;
    da->size = other->size;
    da->data = other->data;
    other->capacity = tmp_capacity;
    other->size = tmp_size;
    other->data = tmp_data;
}

void da_append(DA *da, void *item)
{
    if (!da)
    {
        fprintf(stderr, "da_append(%p, void *item) :: da is NULL\n", da);
        return;
    }

    if (!da->data)
    {
        fprintf(stderr, "da_append(%p, void *item) :: da->data is NULL\n", da);
        da_data_malloc(da);
        if (!da->data)
        {
            fprintf(stderr, "da_append(%p, void *item) :: da->data is NULL even after retry\n", da);
            return;
        }
    }

    if (da->size == da->capacity)
    {
        da_extend(da);

        if (!da->data)
        {
            fprintf(stderr, "da_append(%p, void *item) :: da->data is NULL after extending\n", da);
            return;
        }
    }

    switch (da->type)
    {
    case INT:
        assert(sizeof((int)item) == sizeof(int));
        int **data = (int **)da->data;
        data[da->size++] = (int *)item;
        // da->data[da->size++] = (int *)item;
        break;
    }
}

void da_insert(DA *da, int index, void *item)
{
    if (!da)
    {

        fprintf(stderr, "da_insert(%p, %d, void *item) :: da is NULL\n", da, index);
        return;
    }

    if (!da->data)
    {
        fprintf(stderr, "da_insert(%p, %d, void *item) :: da->data is NULL\n", da, index);
        return;
    }

    if (index < 0 || index >= da->size)
    {
        fprintf(stderr, "da_insert(%p, %d, void *item) :: index out of bounds\n", da, index);
        return;
    }

    void **new_data;
    switch (da->type)
    {
    case INT:
        assert(sizeof((int)item) == sizeof(int));
        new_data = malloc(sizeof(int) * da->capacity);
        break;
    }
    if (!da->data)
    {
        fprintf(stderr, "da_insert(%p, %d, void *item) :: failed to allocate memory for new_data\n", da, index);
        return;
    }

    int idx = 0;
    for (int i = 0; i < index; ++i)
    {
        new_data[idx++] = da->data[i];
    }
    new_data[idx++] = item;
    for (int i = index; i < da->size; ++i)
    {
        new_data[idx++] = da->data[i];
    }

    free(da->data);
    da->data = new_data;

    da->size++;
}

void *da_pop(DA *da)
{
    if (!da)
    {
        fprintf(stderr, "da_pop(%p) :: da is NULL\n", da);
        return NULL;
    }
    if (!da->data)
    {
        fprintf(stderr, "da_pop(%p) :: da->data is NULL\n", da);
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
        fprintf(stderr, "da_remove(%p, %d) :: da is NULL\n", da, index);
        return NULL;
    }
    if (!da->data)
    {
        fprintf(stderr, "da_remove(%p, %d) :: da->data is NULL\n", da, index);
        return NULL;
    }

    if (index < 0 || index >= da->size)
    {
        fprintf(stderr, "da_remove(%p, %d) :: index out of bounds\n", da, index);
        return NULL;
    }

    void **new_data;
    switch (da->type)
    {
    case INT:
        new_data = malloc(sizeof(int) * da->capacity);
        break;
    }
    if (!new_data)
    {
        fprintf(stderr, "da_remove(%p, %d) :: new_data is NULL\n", da, index);
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < index; ++i)
    {
        new_data[idx++] = da->data[i];
    }
    for (int i = index + 1; i < da->size; ++i)
    {
        new_data[idx++] = da->data[i];
    }

    void *res = da->data[index];

    free(da->data);
    da->data = new_data;

    da->size--;
    return res;
}

void da_clear(DA *da)
{
    if (!da)
    {
        fprintf(stderr, "da_clear(%p) :: da is NULL\n", da);
        return;
    }

    da->size = 0;
}

void da_clear_free(DA *da)
{
    if (!da)
    {
        fprintf(stderr, "da_clear_free(%p) :: da is NULL\n", da);
        return;
    }

    if (!da->data)
    {
        fprintf(stderr, "da_clear_free(%p) :: da->data is NULL\n", da);
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
        fprintf(stderr, "da_clear_shrink_cap(%p, %d) :: da is NULL\n", da, new_capacity);
        return;
    }

    if (new_capacity < 0)
    {
        fprintf(stderr, "ca_clear_shrink_cap(%p, %d) :: new_capacity < 0\n", da, new_capacity);
        return;
    }

    da->size = 0;
    da->capacity = new_capacity;

    if (new_capacity == 0)
    {
        da->capacity = DA_DEFAULT_CAPACITY;
    }

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
        fprintf(stderr, "da_debug_print(%p) :: da is NULL\n", da);
        return;
    }

    if (!da->data)
    {
        fprintf(stderr, "da_debug_print(%p) :: da->data is NULL\n", da);
        return;
    }

    for (int i = 0; i < da->size; ++i)
    {
        switch (da->type)
        {
        case INT:
            printf("%d ", (int *)da_get(da, i));
            break;
        }
    }
    printf("\n");
}

void da_debug_print_elem(DA *da, int index)
{
    if (!da)
    {
        fprintf(stderr, "da_debug_print_elem(%p, %d) :: da is NULL\n", da, index);
        return;
    }

    if (!da->data)
    {
        fprintf(stderr, "da_debug_print_elem(%pm %d) :: da->data is NULL\n", da, index);
        return;
    }

    switch (da->type)
    {
    case INT:
        printf("%d\n", (int *)da_get(da, index));
        break;
    }
}

void da_data_free(DA *da)
{
    if (!da)
    {
        fprintf(stderr, "da_data_free(%p) :: da is NULL\n", da);
        return;
    }

    if (!da->data)
    {
        fprintf(stderr, "da_data_free(%p) :: da->data is NULL\n", da);
        return;
    }

    free(da->data);
    da->data = NULL;
    da->size = 0;
    da->capacity = 0;
}

void da_free(DA **da)
{
    if (!da)
    {
        fprintf(stderr, "da_free(%p) :: da is NULL\n", da);
        return;
    }

    if (!*da)
    {
        fprintf(stderr, "da_free(%p) :: *da is NULL\n", da);
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
