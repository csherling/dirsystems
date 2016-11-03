#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

typedef struct stat* sp;

char * readable(long byts){

  char * num = (char *)calloc(3, sizeof(char));
  if(byts > 1000000000){
    byts /= 1000000000;
      num[0] = 'g';
      num[1] = 'b';
  }
  else if(byts > 1000000){
    byts /= 1000000;
      num[0] = 'm';
      num[1] = 'b';
  }
  else if(byts > 1000){
    byts /= 1000;
    num[0] = 'k';
    num[1] = 'b';
  }
  else{
    num[0] = 'b';
  }
  char * str = (char *)calloc(6, sizeof(char));
  sprintf(str, "%ld", byts);
  strcat(str, num);
  return str;
}

void analyzedir(char * dnam){
  DIR * esto;
  esto = opendir(dnam);

  int ctr = 0;
  while(readdir(esto)){
    ctr++;
  }

  rewinddir(esto);
  struct dirent * filez[ctr + 1];

  sp filestat = (sp)malloc(sizeof(sp));

  int j = 0;
  int allsize = 0;
  for(; j < ctr; j++){
    filez[j] = readdir(esto);
    stat(filez[j]->d_name, filestat);
    allsize += filestat->st_size;
  }
  printf("\nStatistics for directory: %s\n", dnam);
  printf("Total Directory Size: %d bytes, %s\n", allsize, readable(allsize)); 

  
  int i = 0;
  printf("Reading Directories:\n");
  for(;i < ctr; i++){
    stat(filez[i]->d_name, filestat);
    if(filez[i]->d_type != 8){
      printf("    %s\n", filez[i]->d_name);
    }
  }
  printf("Reading Files:\n");
  for(i = 0; i < ctr; i++){
    stat(filez[i]->d_name, filestat);
    if(filez[i]->d_type == 8){
      printf("    %s\n", filez[i]->d_name);
    }
  }
  
}

int main(){
  analyzedir(".");
  /* analyzedir(".."); */
  /* analyzedir("../.."); */
  
  return 0;
}
