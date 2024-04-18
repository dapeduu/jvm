#include <stdio.h>
#include <stdint.h>

typedef unsigned char u1;
typedef unsigned short u2;
typedef uint16_t u4;
typedef uint32_t u8; 

struct class_file
{
   u4 magic;
};



int main() {
   FILE *fptr;
   fptr = fopen("test/Test.class", "rb");
   if(fptr == NULL) {
      printf("Not able to open the file.");
      return 1;
   } 

   u1 buffer[4];
   fread(buffer, sizeof(u1), 4, fptr);

   printf("%x%x%x%x", buffer[0], buffer[1], buffer[2], buffer[3]);

   fclose(fptr);
   return 0;
}