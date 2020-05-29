#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MAX_BUF 1024

int main(int argc,char* argv[]){

  FILE* file = fopen(argv[1],"rt");
  FILE* copyfile = fopen(argv[2],"at");
  char a;
  char str1[MAX_BUF] = "chmod 775 "; 
  char *str2 = argv[2];
  strcat(str1,str2);

  if(argc<3){
    printf("usage) %s source_file target_file\n",argv[0]);
    exit(-1);
  }
  while(!feof(file)){ 
    a=fgetc(file);
    fputc(a,copyfile); 
  }

  fclose(copyfile);
  fclose(file);

  system(str1);
  return 0;
}
