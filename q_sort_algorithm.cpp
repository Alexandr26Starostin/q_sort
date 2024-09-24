#include <stdio.h>
#include <assert.h>

#include "list_func_compare.h"
#include "color_print.h"
#include "print_array.h"
#include "q_sort_algorithm.h"

int static partition (int* left, int* right, const size_t len_piece, const size_t len_type, int (*compare_element) (void* first_element, void* second_element), int* array); 

void static change_element (char* first_element, char* second_element, const size_t len_type);

void static print_qsort (int* left, int* left_flag, int* pivot, int* right_flag, int* right, const size_t len_piece, const size_t len_type);





int qsort (int* array, const size_t len_array, const size_t len_type, int (*compare_element) (void* first_element, void* second_element))
{
    assert (array);
    assert (compare_element);

    int* left  = array;                  //Адрес левого конца рассматриваемого кусочка.
    int* right = array + len_array - 1;  //Адрес правого конца рассматриваемого кусочка.

    const size_t len_piece = len_array;  //Длина кусочка.

    partition (left, right, len_piece, len_type, compare_element, array);

    return 0;
}




int static partition (int* left, int* right, const size_t len_piece, const size_t len_type, int (*compare_element) (void* first_element, void* second_element), int* array) 
{
    assert (left);
    assert (right);
    assert (compare_element);

    print_array (array);

    if (len_piece == 0 || len_piece == 1) 
    {
        return 0;
    }

    if (len_piece == 2) 
    {
        if (((*compare_element) (left, right)) >= 0)
        {
            change_element ((char*) left, (char*) right, len_type);
        }

        return 0;
    }

    else
    {

        int* pivot = left + (len_piece / 2);    //Адрес pivot кусочка.

        printf ("left = %d    pivot = %d  right = %d     len_piece = %d\n", *left, *pivot, *right, len_piece);

        int* left_flag  = left;
        int* right_flag = right;

        while (left_flag < right_flag)
        {
            while (((*compare_element) (left_flag, pivot)) < 0 && left_flag < pivot && left_flag < right_flag)
            {
                left_flag += 1;
            }

            if (left_flag >= right_flag) {break;}

            while (((*compare_element) (right_flag, pivot)) >= 0 && right_flag > pivot && left_flag < right_flag)
            {
                right_flag -= 1;
            }

            if (left_flag >= right_flag) {break;}

            int check = 1;

            printf ("left_flag = %d     right_flag = %d \n", *left_flag, *right_flag);

            if (left_flag != pivot && right_flag != pivot)
            {
                change_element ((char*) left_flag, (char*) right_flag, len_type);

                left_flag  += 1;

                if (left_flag == right_flag)
                {
                    check = 0;
                }

                if (check == 1)
                {
                    right_flag -= 1;
                }
            }

            else
            {
                if (left_flag == pivot)
                {
                    change_element ((char*) left_flag, (char*) right_flag, len_type);

                    pivot      = right_flag;
                    left_flag += 1;
                }

                else
                {
                    change_element ((char*) left_flag, (char*) right_flag, len_type);

                    pivot       = left_flag;
                    right_flag -= 1;
                }
            }
            
            print_array (array);
        }

        printf ("\n\n\n");

        size_t len_left_piece = 0;

        for (int* ptr_element = left; ptr_element != pivot; ptr_element += 1) 
        {
            assert (ptr_element >= left && ptr_element <= right);

            len_left_piece += 1;
        }

        size_t len_right_piece = len_piece - len_left_piece;

        if (pivot == left)
        {
            partition (pivot + 1, right, (const size_t) len_right_piece - 1, len_type, compare_element, array); 
            return 0; 
        }

        if (pivot != left)
        {
            partition (left,  pivot - 1, (const size_t) len_left_piece,  len_type, compare_element, array);
        }

        partition (pivot, right, (const size_t) len_right_piece, len_type, compare_element, array);

        return 0;
    }

    return 0;
}

void static change_element (char* first_element, char* second_element, const size_t len_type)
{
    assert (first_element);
    assert (second_element);

    for (int index_byte = 0; index_byte < len_type; index_byte++)
    {
        char temporary             = second_element[index_byte];
        second_element[index_byte] = first_element[index_byte];
        first_element[index_byte]  = temporary;
    }
}
