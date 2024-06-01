#include <stdio.h>
#include <stdlib.h>
#include "./core/core.h"

int main(int argc, char *argv[])
{
    FILE *fptr;
    fptr = fopen(argv[1], "rb");
    if (fptr == NULL)
    {
        printf("Not able to open the file.\n");
        return 1;
    }

    printf("\n============ %s ============\n", argv[1]);

    class_file_t *class_file = read_class_file(fptr);

    printf("magic: %x\n", class_file->magic);
    printf("minor_version: %i\n", class_file->minor_version);
    printf("major_verison: %i\n", class_file->major_version);
    printf("constant_pool_count: %i\n", class_file->constant_pool_count);
    
    free_class_file(class_file);
    fclose(fptr);

    return 0;
}