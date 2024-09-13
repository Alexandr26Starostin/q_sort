#include <stdio.h>
#include <assert.h>

const size_t len_array = 19;

void qsort (int* array, const size_t len_array, size_t len_type, int (*compare_element) (int first_element, int second_element));
int compare_int (int first_element, int second_element);
void print_array (int* array);

int main ()
{
    int array [] = {1, 4, -1, 8, 10, 1, 8, -5, -7, 7, 5, 3, -3, 0, 9, 57, 75, -97, 0};

    qsort (array, 19, sizeof (int), &compare_int);  

    print_array (array);

    return 0;
}

void qsort (int* array, const size_t len_array, size_t len_type, int (*compare_element) (int first_element, int second_element))
{
    assert (array);
    assert (compare_element);

    for (int g = len_array; g > 0; g--)
    {
        for (int i = 0; i < g - 1; i++)
        {
            if (((*compare_element) (array[i], array[i+1])) > 0)
            {
                int temporary = array[i];
                array[i]      = array[i+1];
                array[i+1]    = temporary;
            }
        }
    }
}

int compare_int (int first_element, int second_element)
{
    return first_element - second_element;
}

void print_array (int* array)
{
    assert (array);

    for (int i = 0; i < len_array; i++)
    {
        printf ("%d ", array[i]);
    }
    printf ("\n");
}
