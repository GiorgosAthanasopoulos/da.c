#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define DA_DEFAULT_CAPACITY 10

typedef enum DA_Type
{
    INT,
} DA_Type;

typedef struct DA
{
    void **data;
    int size;
    int capacity;
    DA_Type type;
} DA;

DA *da_init_cap(DA_Type type, int capacity);
DA *da_init(DA_Type type);

void da_data_malloc(DA *da);

void da_extend_cap(DA *da, int by_capacity);
void da_extend(DA *da);

void *da_get(DA *da, int index);
void *da_front(DA *da);
void *da_back(DA *da);
void **da_data(DA *da);

int da_empty(DA *da);
int da_size(DA *da);
void da_reserve(DA *da, int capacity);
int da_capacity(DA *da);
void da_shrink_to_fit(DA *da);
void da_resize(DA *da, int new_capacity);
void da_swap(DA *da, DA *other);

void da_append(DA *da, void *item);
void da_insert(DA *da, int index, void *item);

void *da_pop(DA *da);
void *da_remove(DA *da, int index);

void da_clear(DA *da);
void da_clear_free(DA *da);
void da_clear_shrink_cap(DA *da, int new_capacity);
void da_clear_shrink(DA *da);

void da_debug_print(DA *da);
void da_debug_print_elem(DA *da, int index);

void da_data_free(DA *da);
void da_free(DA **da);

#endif // DYNAMIC_ARRAY_H
