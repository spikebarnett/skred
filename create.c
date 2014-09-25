#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char **argv)
{
  FILE *fp;
  int i,j;
  for (i = 0; i < 1000; ++i)
  {
    char dir[3];
    sprintf(dir,"%i",i);
    mkdir(dir, 0777);
    for (j = 0; j < 1000; ++j)
    {
      char name[3],path[7];  
      sprintf(name,"%i",j);
      strcpy(path,dir);
      strcat(path,"/");
      strcat(path,name);
      
      fp = fopen(path, "w");
      fclose(fp);
    }
  }
  return 0;
}
