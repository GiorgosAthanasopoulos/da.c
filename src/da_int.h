#ifndef DYNAMIC_ARRAY_INT_H
#define DYNAMIC_ARRAY_INT_H

#include "da.h"

int da_get_i(DA *da, int index);
int da_front_i(DA *da);
int da_back_i(DA *da);
int *da_data_i(DA *da);

void da_append_i(DA *da, int item);
void da_insert_i(DA *da, int index, int item);

int da_pop_i(DA *da);
int da_remove_i(DA *da, int index);

#endif // DYNAMIC_ARRAY_INT_H
