#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv) {
   if(argc != 5){
      printf("Incorrect number of arguments\n");
      return 1;
   }

   FILE* ptr = fopen(argv[1], "w");
   if(ptr == NULL){
      printf("Unable to open file %s\n", argv[1]);
      return 2;
   }

   int i, length = atoi(argv[2]), low = atoi(argv[3]), high = atoi(argv[4]);
   fprintf(ptr, "%d\n", length);

   srand(time(NULL));

   for(i = 0; i < length; i++)
      fprintf(ptr,"%d\n", rand() % (high - low) + low);

   fclose(ptr);

   return 0;
}


