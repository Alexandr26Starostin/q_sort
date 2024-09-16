#include <stdio.h>
#include <assert.h>

const size_t len_array = 19;

void qsort (void* array, const size_t len_array, const size_t len_type, int (*compare_element) (void* first_element, void* second_element));
int compare_int (void* first_element, void* second_element);
void change_elemet (char* first_element, char* second_element, const size_t len_type);
void print_array (int* array);

int main ()
{
    int array [] = {1, 4, -1, 8, 10, 1, 8, -5, -7, 7, 5, 3, -3, 0, 9, 57, 75, -97, 0};

    qsort (array, 19, sizeof (int), &compare_int);  

    print_array (array);

    return 0;
}

void qsort (void* array, const size_t len_array, const size_t len_type, int (*compare_element) (void* first_element, void* second_element))
{
    assert (array);
    assert (compare_element);

    for (int g = len_array; g > 0; g--)
    {
        for (int i = 0; i < g - 1; i++)
        {
            if (((*compare_element) ((char*) array + i * len_type, (char*) array + (i + 1) * len_type)) > 0)
            {
                change_elemet ((char*) array + i * len_type, (char*) array + (i + 1) * len_type, len_type);
            }
        }
    }
}

void change_elemet (char* first_element, char* second_element, const size_t len_type)
{
    assert (first_element);
    assert (second_element);

    for (int i = 0; i < len_type; i++)
    {
        char temporary    = second_element[i];
        second_element[i] = first_element[i];
        first_element[i]  = temporary;
    }

    

}

int compare_int (void* first_element, void* second_element)
{
    return *((int*) first_element) - *((int*)second_element);
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
