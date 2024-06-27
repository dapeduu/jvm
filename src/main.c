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
    loaded_classes_t *loaded_class = malloc(sizeof(loaded_classes_t));
    char *file_path = argv[2];

    int is_not_reader = strcmp(PROGRAM_OPTION, "-r");
    u4_t * args = calloc(2, sizeof(u4_t));
    args[0] = 12;
    args[1] = 3;

    if (is_not_reader) {
        printf("Carregador:\n");
        load_class(class_file, file_path);
        printf("Execução:\n");

        // encontrar main
        loaded_classes_t * classes = load_class(class_file, file_path);

        field_method_info_t * main_method_info;
        for (size_t i = 0; i < classes->class_file->methods_count; i++)
        {
            field_method_info_t * current_method = &classes->class_file->methods[i];
            u2_t name_index = current_method->name_index;
            char * method_name = get_constant_pool_value(classes->class_file->constant_pool, name_index);

            if (strcmp(method_name, "main")) { continue; }

            main_method_info = current_method;
        }
        
        if (main_method_info == NULL) {
            printf("Erro: Não existe o método main nessa classe");
            exit(1);
        }


        // empilhar frames a partir dela

        // frame_t * frame = get_frame(
        //             class_file->methods_count,
        //             class_file->methods,
        //             "test",
        //             2,
        //             args,
        //             class_file->constant_pool);
        // u4_t result = run_frame(frame);
        // printf("Resultado da execução: %i\n", result);

        printf("Chegou ao fim da execução");
    } else {
        printf("Exibidor:\n");
        display_class_file(class_file, FILE_PATH);
    }

    fclose(fptr);

    return 0;
}
