#include <stdio.h>
#include <assert.h>

#include "q_sort_algorithm.h"
#include "list_func_compare.h"
#include "print_array.h"

int main ()
{
    int array [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    print_array (array);

    qsort (array, 13, sizeof (int), &compare_int);  

    print_array (array);

    return 0;
}
