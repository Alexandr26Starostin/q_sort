#include <stdio.h>
#include <assert.h>

#include "list_func_compare.h"
#include "color_print.h"
#include "print_array.h"
#include "q_sort_algorithm.h"

int static partition (char* left, char* right, const size_t len_piece, const size_t len_type, int (*compare_element) (void* first_element, void* second_element)); 

void static change_element (char* first_element, char* second_element, const size_t len_type);

void static print_qsort (int* left, int* left_flag, int* pivot, int* right_flag, int* right, const size_t len_piece, const size_t len_type);


int qsort (void* array, const size_t len_array, const size_t len_type, int (*compare_element) (void* first_element, void* second_element))
{
    assert (array);
    assert (compare_element);

    char* left  = (char*) array;                               //Адрес левого конца рассматриваемого кусочка.
    char* right = (char*) array + (len_array - 1) * len_type;  //Адрес правого конца рассматриваемого кусочка.

    const size_t len_piece = len_array;                        //Длина кусочка.

    partition (left, right, len_piece, len_type, compare_element);

    return 0;
}


int static partition (char* left, char* right, const size_t len_piece, const size_t len_type, int (*compare_element) (void* first_element, void* second_element)) 
{
    assert (left);
    assert (right);
    assert (compare_element);

    if (len_piece == 0 || len_piece == 1)        //Если кусочек не имеет символов или имеет один символ, то его не нужно сортировать.
    {
        return 0;
    }

    else
    {

        char* pivot = left + (len_piece / 2) * len_type;   //Адрес pivot. !!! pivot - плохой элемент.

        char* left_flag  = left;                           //Начальный левый  флаг. Этот флаг будет передвигаться от левого  конца кусочка вправо. Флаг указывает на элемент массива.
        char* right_flag = right;                          //Начальный правый флаг. Этот флаг будет передвигаться от правого конца кусочка влево.  Флаг указывает на элемент массива.

        while (left_flag < right_flag)                     //Пока флаги не пересеклись, будет продолжать менять элементы местами.
        {
            while (((*compare_element) (left_flag, pivot)) < 0 && left_flag < pivot && left_flag < right_flag)      //Пропускает хорошие левые элементы. Хороший левый элемент: < pivot, левее pivot, левее правого флага.
            {
                left_flag += len_type;
            }

            if (left_flag >= right_flag) {break;}          //Прерывает, если флаги пересеклись.

            while (((*compare_element) (right_flag, pivot)) >= 0 && right_flag > pivot && left_flag < right_flag)   //Пропускает хорошие правые элементы. Хороший правый элемент: > pivot, правее pivot, правее левого флага.  
            {
                right_flag -= len_type;
            }

            if (left_flag >= right_flag) {break;}            //Прерывает, если флаги пересеклись.

            if (left_flag != pivot && right_flag != pivot)   //Если оба флага не совпали с pivot, то меняет плохие элементы местами и двигает флаги.
            {
                change_element (left_flag, right_flag, len_type);

                left_flag  += len_type;

                if (left_flag != right_flag)                 //Прерывает, если флаги пересеклись. Пример: left_flag = 4 и right_flag = 5  ->  left_flag = 5 и right_flag = 5 (!персеклись)   Без этой проверки в конце было бы: left_flag = 5 и right_flag = 4
                {
                    right_flag -= len_type;
                }
            }

            else
            {
                if (left_flag == pivot)                 //Если левый флаг совпал с pivot, то меняет плохие элементы; не двигает правый флаг, тк он теперь указывает на pivot, те на плохой элемент; двигает левый флаг.
                {
                    change_element (left_flag, right_flag, len_type);

                    pivot      = right_flag;
                    left_flag += len_type;
                }

                else                  //Если правый флаг совпал с pivot, то меняет плохие элементы; не двигает левый флаг, тк он теперь указывает на pivot, те на плохой элемент; двигает правый флаг.
                {
                    change_element (left_flag, right_flag, len_type);

                    pivot       = left_flag;
                    right_flag -= len_type;
                }
            }
        }

        size_t len_left_piece = 0;

        for (char* ptr_element = left; ptr_element != pivot; ptr_element += len_type)   //Считает количество символов слева от pivot без pivot.
        {
            assert (ptr_element >= left && ptr_element <= right);

            len_left_piece += 1;
        }

        size_t len_right_piece = len_piece - len_left_piece;          //Считает количество символов справа от pivot с pivot.

        if (pivot == left)   //Если pivot - cамый левый элемент, то выбрасывает его из рассмотрения и начинает сортировать элементы справа от pivot. (слева от pivot элементов нет.)
        {
            partition (pivot + len_type, right, (const size_t) len_right_piece - 1, len_type, compare_element);   //(len_right_piece - 1) - длина правого кусочка без pivot.
            return 0; 
        }
    
        partition (left,  pivot - len_type, (const size_t) len_left_piece,  len_type, compare_element);    //Сортирует элемента слева  от pivot, не включая его.
        partition (pivot, right,            (const size_t) len_right_piece, len_type, compare_element);    //Сортирует элемента справа от pivot,    включая его.

        return 0;
    }
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
