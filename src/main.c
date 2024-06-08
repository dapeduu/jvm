#include <stdio.h>
#include <stdlib.h>
#include "./core/core.h"
#include "./core/consts.h"
#include "./display.h"

int main(int argc, char *argv[])
{
    FILE *fptr;
    fptr = fopen(argv[1], "rb");
    if (fptr == NULL)
    {
        printf("Not able to open the file.\n");
        return 1;
    }

    class_file_t *class_file = read_class_file(fptr);
    display_class_file(class_file, argv[1]);

    fclose(fptr);

    return 0;
}
