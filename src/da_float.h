#ifndef DYNAMIC_ARRAY_INT_H
#define DYNAMIC_ARRAY_INT_H

#include "da.h"

float da_get_f(DA *da, int index);
float da_front_f(DA *da);
float da_back_f(DA *da);
float *da_data_f(DA *da);

void da_append_f(DA *da, float item);
void da_insert_f(DA *da, int index, float item);

float da_pop_f(DA *da);
float da_remove_f(DA *da, int index);

#endif // DYNAMIC_ARRAY_INT_H
