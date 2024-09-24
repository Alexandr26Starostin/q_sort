#include <stdio.h>
#include <assert.h>

#include "print_array.h"

void print_array (int* array, const size_t len_array)
{
    assert (array);

    for (size_t index_element = 0; index_element < len_array; index_element++)
    {
        assert (index_element <= len_array - 1);

        printf ("%d ", array[index_element]);
    }
    printf ("\n");
}