#include <stdio.h>
#include <stdlib.h>
#include "dot_class.h"

u1_t read_u1(FILE* fptr) {
   u1_t value; 

   value = getc(fptr);

   return value;
} 

u2_t read_u2(FILE* fptr) {
   u2_t value; 
   u1_t buffer[2];

   fread(buffer, sizeof(u1_t), 2, fptr);

   value = (buffer[0] << 8) | buffer[1];

   return value;
} 

u4_t read_u4(FILE* fptr) {
   u4_t value; 
   u1_t buffer[4];

   fread(buffer, sizeof(u1_t), 4, fptr);

   value = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];

   return value;
}

class_file_t* read_class_file(FILE* fptr) {
   class_file_t* class_file = malloc(sizeof(class_file));

   class_file->magic = read_u4(fptr);
   class_file->minor_version = read_u2(fptr);
   class_file->major_version = read_u2(fptr);
   class_file->constant_pool_count = read_u2(fptr);
   class_file->constant_pool->tag = read_u1(fptr);

   switch (class_file->constant_pool->tag)
   {
   case 10:
      class_file->constant_pool->info.Methodref.class_index = read_u2(fptr);
      class_file->constant_pool->info.Methodref.name_and_type_index = read_u2(fptr);
      break;
   
   default:
      break;
   }

   return class_file;
}

int main() {

   FILE *fptr;
   fptr = fopen("test/fibonacci.class", "rb");
   if(fptr == NULL) {
      printf("Not able to open the file.");
      return 1;
   } 

   class_file_t* class_file = read_class_file(fptr);

   printf("%x\n", class_file->magic);
   printf("%i\n", class_file->minor_version);
   printf("%i\n", class_file->major_version);
   printf("%i\n", class_file->constant_pool_count);
   printf("%i\n", class_file->constant_pool->tag);
   printf("%i\n", class_file->constant_pool->info);
   
   free(class_file);
   fclose(fptr);

   return 0;
}