#define STR_IMPLEMENTATION
#include "../str.h"

int main()
{
    Str msg = str("Hello");

    str_concat(&msg, ", World!");

    str_info(msg);

    return 0;
}

