#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#include "color_print.h"

void print_with_color (enum style st, enum color_of_text tex, enum color_of_background bg, const char* line, ...)        //переменные - сокращение типов
{
    assert (line);

    printf ("\033[%d;%d;%dm", st, tex, bg);

    va_list arguments;

    va_start (arguments, line);
    vprintf (line, arguments);
    va_end (arguments);

    printf ("\033[0m");
}
