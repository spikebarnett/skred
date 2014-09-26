#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char **argv)
{
  FILE *fp;
  int i,j;
  for (i = 0; i < 2000; ++i)
  {
    char dir[255];
    sprintf(dir,"%i",i);
    mkdir(dir, 0777);
    for (j = 0; j < 2000; ++j)
    {
      char name[255],path[512];  
      sprintf(name,"%i",j);
      strcpy(path,dir);
      strcat(path,"/");
      strcat(path,name);
      
      printf(path); printf("\n");
      
      fp = fopen(path, "w");
      fclose(fp);
    }
  }
  return 0;
}
