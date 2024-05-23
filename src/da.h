#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

// == EXTENDING ==
//
// To extend the dynamic array with your own types follow these simple rules:
//
//   1. Firstly add a name for your new type to DA_Type enum definition. (e.g. FLOAT)
//
//   2. In da.c whenever u see a switch(da->type) implement the case of your new type. Look for previous implementations
//   of other types for reference!
//
//   3. Profit!
//
// !== EXTENDING !==

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

// Create a dynamic array with the given type and capacity
DA *da_init_cap(DA_Type type, int capacity);
// Create a dynamic array with the given type and default capacity (10)
DA *da_init(DA_Type type);

// Reallocates the dynamic array's data
void da_data_malloc(DA *da);

// Extend the dynamic array's capacity by the given number
void da_extend_cap(DA *da, int by_capacity);
// Extend the dynamic arrray's capacity by the default value (10)
void da_extend(DA *da);

// Get the index-th element of the dynamic array. Bound checked
void *da_get(DA *da, int index);
// Get the first/front element of the dynamic array
void *da_front(DA *da);
// Get the last/back element of the dynamic array
void *da_back(DA *da);
// Get the pointer to the dynamic array's data
void **da_data(DA *da);

// Return whether the dynamic array is empty or not
int da_empty(DA *da);
// Return the size of the dynamic array
int da_size(DA *da);
// Reserve `capacity` extra spots in dynamic array
void da_reserve(DA *da, int capacity);
// Return the dynamic array's capacity
int da_capacity(DA *da);
// Shrink the dynamic array to fit to the actual contetns
void da_shrink_to_fit(DA *da);
// Resize the dynamic array to `new_capacity`
void da_resize(DA *da, int new_capacity);
// Swap the contents of the two dynamic arrays provided
void da_swap(DA *da, DA *other);

// Append an element to the dynamic array
void da_append(DA *da, void *item);
// Insert an element at a specific index in the dynamic array
void da_insert(DA *da, int index, void *item);

// Pop(remove) last value from dynamic array and return it
void *da_pop(DA *da);
// Remove index-th element from the dynamic array and return it
void *da_remove(DA *da, int index);

// Clear the contents of the dynamic array
void da_clear(DA *da);
// Clear the contents of the dynamic array and free its underlying memory
void da_clear_free(DA *da);
// Clear the contents of the dynamic array and shirnk to `new_capacity`
void da_clear_shrink_cap(DA *da, int new_capacity);
// Clear the contents of the dynamic array and shrink to default capacity (10)
void da_clear_shrink(DA *da);

// Prints all of the dynamic array\'s elements
void da_debug_print(DA *da);
// Prints the index-th element of the dynamic array
void da_debug_print_elem(DA *da, int index);

// Free the dynamic array's underlying data memory
void da_data_free(DA *da);
// Free the whole dynamic array
void da_free(DA **da);

#endif // DYNAMIC_ARRAY_H
