#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "class_loader.h"
#include "runtime_data_area.h"
#include "execution_engine.h"

int main(int argc, char *argv[]) {
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
    loaded_classes_t * loaded_classes = malloc(sizeof(loaded_classes_t));

    int is_not_reader = strcmp(PROGRAM_OPTION, "-r");
    u4_t * args = calloc(2, sizeof(u4_t));
    args[0] = 12;
    args[1] = 3;

    if (is_not_reader) {
        printf("Execução:\n");
        frame_t * frame = get_frame(class_file->methods_count,
                    class_file->methods,
                    "test",
                    2,
                    args,
                    class_file->constant_pool);
        u4_t result = run_frame(frame);
        printf("Resultado da execução: %i\n", result);
    } else {
        printf("Exibidor:\n");
        display_class_file(class_file, FILE_PATH);
        printf("Teste: %s", get_constant_pool_value(class_file->constant_pool, 4));
        // display_class(class);
    }

    fclose(fptr);

    return 0;
}
