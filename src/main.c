#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "class_loader.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("You have to pass 2 args.\n");
        printf("Reader: jvm -r ./path/to/file\n");
        printf("Execution: jvm -e ./path/to/file\n");
        return 1;
    }

    char * PROGRAM_OPTION = argv[1]; 
    char * FILE_PATH = argv[2]; 

    FILE *fptr;
    fptr = fopen(FILE_PATH, "rb");
    if (fptr == NULL)
    {
        printf("Not able to open the file.\n");
        return 1;
    }

    class_file_t *class_file = read_class_file(fptr);
    
    int is_not_reader = strcmp(PROGRAM_OPTION, "-r");
    if (is_not_reader) {
        printf("Execução:\n");
        // printf("Class file: %s\n", argv[2]);
        display_class_file(class_file, FILE_PATH);
    } else {
        printf("Exibidor:\n");
        display_class_file(class_file, FILE_PATH);
        printf("Teste: %s", get_constant_pool_value(class_file->constant_pool, 4));
        // display_class(class);
    }

    fclose(fptr);

    return 0;
}
