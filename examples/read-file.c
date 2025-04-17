#define STR_IMPLEMENTATION
#include "../str.h"

/*
 * HELLO FROM SOURCE FILE
*/

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Please, provide a text file as argument\n");
        fprintf(stderr, "USAGE: %s <file>\n", argv[0]);
        return 1;
    }

    Str src = str_from_file(argv[1]);

    str_info(src);

    return 0;
}

