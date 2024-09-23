#include <stdio.h>
#include <assert.h>

#include "list_func_compare.h"
int compare_int (void* first_element, void* second_element)
{
	assert (first_element);
	assert (second_element);
	
    return *((int*) first_element) - *((int*)second_element);
}

