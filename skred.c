#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static int rm(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
  if(tflag == FTW_F)  unlink(fpath);
  if(tflag == FTW_SL) unlink(fpath);
  if(tflag == FTW_DP)  rmdir(fpath);
  return 0;
}

int main (int argc, char **argv)
{
	int sanity = 1;
	char path[1024];
	if(argc < 2)
	{
		printf("usage: skred /path/to/targetdirectory/ [..]\n");
		exit(EXIT_FAILURE);
	} else {
		strcpy(path,argv[1]);
	}

	if(argc > 2)
	{
		if(!strcmp(argv[2],"--fuck-it-well-do-it-live"))
		{
			sanity = 0;
			printf("Disabling sanity checks. Remember, you brought this on yourself...\n");
		}
	}

	if(sanity == 1)
	{
		if(path[0] != '/')
		{
			printf("skred: Path must be absolute\n");
			printf("use --fuck-it-well-do-it-live to skip sanity checks at your own risk\n");
			exit(EXIT_FAILURE);
		}

		struct stat st;
		int err = lstat(path, &st);
		if(-1 == err) {
			if(ENOENT == errno) {
				perror("skred");
				exit(EXIT_FAILURE);
			} else {
				perror("skred");
				exit(EXIT_FAILURE);
			}
		} else {
			if(S_ISLNK(st.st_mode))
			{
				printf("skred: Path must not contain symbolic links\n");
				printf("use --fuck-it-well-do-it-live to skip sanity checks at your own risk\n");
				exit(EXIT_FAILURE);
			}
			if(S_ISDIR(st.st_mode))
			{
				if (path[strlen(path)-1] != '/') strcat(path,"/");
			} else {
				printf("skred: Path must end with a directory");
				printf("use --fuck-it-well-do-it-live to skip sanity checks at your own risk\n");
				exit(EXIT_FAILURE);
			}
		}

		char tmp[1024];
		strcpy(tmp,path);
		int i;
		for(i = strlen(path); i > 0; --i)
		{
			if(tmp[i] == '/')
			{
				tmp[i] = '\0';
				lstat(tmp, &st);
				if(S_ISLNK (st.st_mode))
				{
					printf("skred: Path must not contain symbolic links\n");
					printf("use --fuck-it-well-do-it-live to skip sanity checks at your own risk\n");
					exit(EXIT_FAILURE);
				}
			} else {
				tmp[i] = '\0';
			}
		}
		
		int count; char *s = path;
		for (count = 0; s[count]; s[count]=='/' ? count++ : *s++);
		
		if(count < 3)
		{
			printf("skred: Path must be at least two directories deep from /\n");
			printf("use --fuck-it-well-do-it-live to skip sanity checks at your own risk\n");
			exit(EXIT_FAILURE);
		}
	}
	/*
	if (nftw((argc < 2) ? "." : argv[1], rm, 20, FTW_DEPTH|FTW_PHYS|FTW_MOUNT) == -1)
	{
			perror("skred");
			exit(EXIT_FAILURE);
	}
	*/
	return 0;
}
