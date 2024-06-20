#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./core/core.h"
#include "./display.h"
#include "./runtime_data_area/method_area.h"
#include "./class_loader/bootstrap_class_loader.c"
#include "./helpers/hash_table_helpers.c"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("You have to pass 2 args.\n");
        printf("Reader: jvm -r ./path/to/file\n");
        printf("Execution: jvm -e ./path/to/file\n");
        return 1;
    }

    FILE *fptr;
    fptr = fopen(argv[2], "rb");
    if (fptr == NULL)
    {
        printf("Not able to open the file.\n");
        return 1;
    }

    class_file_t *class_file = read_class_file(fptr);

    int is_not_reader = strcmp(argv[1], "-r");
    if (is_not_reader) {
        printf("Execução\n");
        // printf("Class file: %s\n", argv[2]);
        load_class_file(class_file);
    } else {
        display_class_file(class_file, argv[1]);
        // display_class(class);
    }

    fclose(fptr);

    return 0;
}
