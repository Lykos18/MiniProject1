#include <stdio.h>

int main(){
  FILE *fp;

//creating writable file
fp = fopen("test2.txt", "a");
//Add text to document
  fprintf(fp, "Hello!");
//close the file
  fclose(fp);
}
