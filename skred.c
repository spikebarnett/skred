#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <unistd.h>

static int rm(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
  if (tflag == FTW_F) unlink(fpath);
  if (tflag == FTW_DP) rmdir(fpath);
  return 0;
}

int main (int argc, char **argv)
{ 
  if (nftw((argc < 2) ? "." : argv[1], rm, 20, FTW_DEPTH|FTW_PHYS) == -1)
  {
      perror("skred");
      exit(EXIT_FAILURE);
  }
  return 0;
}
