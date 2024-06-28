/**
 * @file main.c
 * @brief Arquivo principal do projeto.
 *
 * Recebe os argumentos passados pelo terminal, e escolhe entre o modo leitor-exibidor e
 * o modo execução. No modo leitor-exibidor, exibe as informações do arquivo .class passado
 * como argumento. No modo execução, faz a execução do arquivo .class passado como argumento.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "class_loader.h"
#include "runtime_data_area.h"
#include "execution_engine.h"

/**
 * @brief Função main.
 *
 * Escolhe entre o modo leitor-exibidor e o modo execução.
 *
 * @param[in]  param1  argc, argv.
 * @return 1 em caso de erro, 0 em caso de sucesso.
 */

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
        printf("Execução:\n");

        // encontrar main
        loaded_classes_t * classes = load_class(class_file, file_path);

        // empilhar frames a partir dela
        frame_t * frame = get_frame(
                    "main",
                    0,
                    NULL,
                    class_file);
                    
        u4_t result = run_frame(frame);
        // printf("Resultado da execução: %i\n", result);

        printf("Chegou ao fim da execução");
    } else {
        printf("Exibidor:\n");
        display_class_file(class_file, FILE_PATH);
    }

    fclose(fptr);

    return 0;
}
