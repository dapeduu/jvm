#include <stdio.h>
#include <stdlib.h>
#include "./core/core.h"
#include "./display.h"
#include "./runtime_data_area/method_area.h"
#include "./class_loader/bootstrap_class_loader.c"

#define IS_READER 0

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
    
    if (IS_READER) {
        display_class_file(class_file, argv[1]);
    } else {
        method_area_t *method_area = newHashTable();
        // display_class(class);
    }

    fclose(fptr);

    return 0;
}
