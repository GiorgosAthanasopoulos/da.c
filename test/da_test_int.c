#include <assert.h>

#include "../src/da.h"
#include "../src/da_int.h"

void test_init()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_free(&da);
}

void test_init_cap()
{
    int capacity = 12;
    DA *da = da_init_cap(INT, capacity);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == capacity);
    assert(da->type == INT);

    da_free(&da);
}

void test_extend_cap()
{
    int by_capacity = 12;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_extend_cap(da, by_capacity);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY + by_capacity);
    assert(da->type == INT);

    da_free(&da);
}

void test_extend()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_extend(da);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY * 2);
    assert(da->type == INT);

    da_free(&da);
}

void test_get()
{
    int item = 1;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, item);

    assert(da);
    assert(da->data);
    assert(da->size == 1);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da_get_i(da, 0) == item);

    da_free(&da);
}

void test_front()
{
    int first = 1, last = 2;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, first);
    da_append_i(da, last);

    assert(da);
    assert(da->data);
    assert(da->size == 2);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da_front_i(da) == first);

    da_free(&da);
}

void test_back()
{
    int first = 1, last = 2;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, first);
    da_append_i(da, last);

    assert(da);
    assert(da->data);
    assert(da->size == 2);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da_back_i(da) == last);

    da_free(&da);
}

void test_data()
{
    DA *da = da_init(INT);
    int by_capacity = 2;

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da->data == da_data(da));

    da_extend_cap(da, by_capacity);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY + by_capacity);
    assert(da->type == INT);
    assert(da->data == da_data(da));

    da_free(&da);
}

void test_empty()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da_empty(da) == 1);

    da_append_i(da, 1);

    assert(da);
    assert(da->data);
    assert(da->size == 1);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da_empty(da) == 0);

    da_free(&da);
}

void test_size()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da_size(da) == 0);

    da_append_i(da, 1);

    assert(da);
    assert(da->data);
    assert(da->size == 1);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da_size(da) == 1);

    da_free(&da);
}

void test_reserve()
{
    DA *da = da_init(INT);
    int by_capacity = 2;

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_reserve(da, by_capacity);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY + by_capacity);
    assert(da->type == INT);

    da_free(&da);
}

void test_capacity()
{
    DA *da = da_init(INT);
    int by_capacity = 2;

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da_capacity(da) == DA_DEFAULT_CAPACITY);

    da_extend_cap(da, by_capacity);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY + by_capacity);
    assert(da->type == INT);
    assert(da_capacity(da) == DA_DEFAULT_CAPACITY + by_capacity);

    da_free(&da);
}

void test_shrink_to_fit()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, 1);
    da_shrink_to_fit(da);

    assert(da);
    assert(da->data);
    assert(da->size == 1);
    assert(da->capacity == 1);
    assert(da->type == INT);

    da_free(&da);
}

void test_resize()
{
    int new_cap = 3;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, 1);
    da_append_i(da, 2);
    da_resize(da, new_cap);

    assert(da);
    assert(da->data);
    assert(da->size == 2);
    assert(da->capacity == new_cap);
    assert(da->type == INT);

    da_free(&da);
}

void test_swap()
{
    int first = 1, last = 2;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, first);

    assert(da);
    assert(da->data);
    assert(da->size == 1);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    DA *other = da_init(INT);

    assert(other);
    assert(other->data);
    assert(other->size == 0);
    assert(other->capacity == DA_DEFAULT_CAPACITY);
    assert(other->type == INT);

    da_append_i(other, last);

    assert(other);
    assert(other->data);
    assert(other->size == 1);
    assert(other->capacity == DA_DEFAULT_CAPACITY);
    assert(other->type == INT);

    da_swap(da, other);

    assert(da);
    assert(da->data);
    assert(da->size == 1);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    assert(other);
    assert(other->data);
    assert(other->size == 1);
    assert(other->capacity == DA_DEFAULT_CAPACITY);
    assert(other->type == INT);

    assert(da_front_i(other) == first);
    assert(da_front_i(da) == last);

    da_free(&other);
    da_free(&da);
}

void test_append()
{
    int item = 1;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, item);

    assert(da);
    assert(da->data);
    assert(da->size == 1);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(da_front_i(da) == item);

    da_free(&da);
}

void test_insert()
{
    int item = 4;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, 1);
    da_append_i(da, 2);
    da_append_i(da, 3);
    da_insert_i(da, 0, item);

    int front = da_front_i(da);

    assert(da);
    assert(da->data);
    assert(da->size == 4);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);
    assert(front == item);

    da_free(&da);
}

void test_pop()
{
    int item = 1;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, item);

    assert(da);
    assert(da->data);
    assert(da->size == 1);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    int res = da_pop_i(da);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    assert(res == item);

    da_free(&da);
}

void test_remove()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, 1);
    da_append_i(da, 2);
    da_append_i(da, 3);

    assert(da);
    assert(da->data);
    assert(da->size == 3);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    int res = da_remove_i(da, 1);

    assert(da);
    assert(da->data);
    assert(da->size == 2);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    assert(res == 2);
    assert(da_get_i(da, 1) == 3);

    da_free(&da);
}

void test_clear()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, 1);

    assert(da);
    assert(da->data);
    assert(da->size == 1);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_clear(da);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_free(&da);
}

void test_clear_shrink()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, 1);
    da_append_i(da, 2);
    da_append_i(da, 3);

    assert(da);
    assert(da->data);
    assert(da->size == 3);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_clear_shrink(da);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_free(&da);
}

void test_clear_shrink_cap()
{
    int new_capacity = 5;
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_append_i(da, 1);
    da_append_i(da, 2);
    da_append_i(da, 3);

    assert(da);
    assert(da->data);
    assert(da->size == 3);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_clear_shrink_cap(da, new_capacity);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == new_capacity);
    assert(da->type == INT);

    da_free(&da);
}

void test_debug_print()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_free(&da);
}

void test_debug_print_elem()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_free(&da);
}

void test_data_free()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_data_free(da);
    assert(!da->data);

    da_free(&da);
}

void test_free()
{
    DA *da = da_init(INT);

    assert(da);
    assert(da->data);
    assert(da->size == 0);
    assert(da->capacity == DA_DEFAULT_CAPACITY);
    assert(da->type == INT);

    da_free(&da);
    assert(!da);
}

int main()
{
    test_init();
    test_init_cap();
    test_extend_cap();
    test_extend();
    test_get();
    test_front();
    test_back();
    test_data();
    test_empty();
    test_size();
    test_reserve();
    test_capacity();
    test_shrink_to_fit();
    test_resize();
    test_swap();
    test_append();
    test_insert();
    test_pop();
    test_remove();
    test_clear();
    test_clear_shrink();
    test_clear_shrink_cap();
    test_debug_print();
    test_debug_print_elem();
    test_data_free();
    test_free();
}
