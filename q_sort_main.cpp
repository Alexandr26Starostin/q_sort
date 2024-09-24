#include <stdio.h>
#include <assert.h>

#include "q_sort_algorithm.h"
#include "list_func_compare.h"
#include "print_array.h"

int main ()
{
    int array [] = {3, 3, 3, 3, 3, 5, -60, 7, 3, 4, 11, 12, 13};  

    print_array (array, 13);

    qsort (array, 13, sizeof (int), &compare_int);  

    print_array (array, 13);

    return 0;
}
