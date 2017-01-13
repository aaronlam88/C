#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   FILE *fp;
   char str[60];

   /* opening file for reading */
   fp = fopen("myfile.txt" , "r");
   if(fp == NULL) 
   {
      perror("Error opening file");
      return(-1);
   }
   if( fgets (str, 60, fp)!=NULL ) 
   {
      char* temp = strtok(str, ", ");
      while(temp != NULL){
         printf("'%s'\n", temp);
         temp = strtok(NULL, ", ");
      }
   }
   fclose(fp);
   
   return(0);
}