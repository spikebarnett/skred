#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static int rm(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
  int res;
  if (tflag == FTW_F) res = unlink(fpath);
  if (tflag == FTW_D) res = rmdir(fpath);
  if (res == -1)
  {
    printf(strerror(errno));
    //printf(err); printf("\n");
  }
  return 0;
}

int main (int argc, char **argv)
{
  char err[15];
  sprintf(err,"%i", EACCES ); printf ("EACCES:  "); printf(err); printf("\n");
  sprintf(err,"%i", EBUSY  ); printf ("EBUSY:   "); printf(err); printf("\n");
  sprintf(err,"%i", EEXIST ); printf ("EEXIST:  "); printf(err); printf("\n");
  sprintf(err,"%i", EINVAL ); printf ("EINVAL:  "); printf(err); printf("\n");
  sprintf(err,"%i", EIO    ); printf ("EIO:     "); printf(err); printf("\n");
  sprintf(err,"%i", ELOOP  ); printf ("ELOOP:   "); printf(err); printf("\n");
  sprintf(err,"%i", ENOENT ); printf ("ENOENT:  "); printf(err); printf("\n");
  sprintf(err,"%i", ENOTDIR); printf ("ENOTDIR: "); printf(err); printf("\n");
  sprintf(err,"%i", EPERM  ); printf ("EPERM:   "); printf(err); printf("\n");
  sprintf(err,"%i", EROFS  ); printf ("EROFS:   "); printf(err); printf("\n");
  
  if (nftw((argc < 2) ? "." : argv[1], rm, 20, FTW_DEPTH|FTW_PHYS) == -1)
  {
      perror("nftw");
      exit(EXIT_FAILURE);
  }
  return 0;
}
