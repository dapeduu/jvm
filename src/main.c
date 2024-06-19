#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./core/core.h"
#include "./display.h"
#include "./runtime_data_area/method_area.h"
#include "./class_loader/bootstrap_class_loader.c"

hash_table_t* newHashTable(short table_size) {
  hash_table_t* hash_table = (hash_table_t*) malloc(sizeof(hash_table_t));
  hash_table->table_size = table_size;
  hash_table->data_size = 0;
  hash_table->entries = calloc(hash_table->table_size, sizeof(key_value_t*));
  
  return hash_table;
}

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
        printf("Execução");
    } else {
        display_class_file(class_file, argv[1]);
        // method_area_t *method_area = newHashTable();
        // display_class(class);
    }

    fclose(fptr);

    return 0;
}
