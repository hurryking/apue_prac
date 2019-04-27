#include "apue.h"
#include <dirent.h>

int main(int argc, char const *argv[])
{
	DIR *dp;
	struct dirent *dirp;

	if (argc != 2) {
		err_quit("usage: ls direction_name");
	}

	if ((dp = opendir(argv[1])) == NULL) {
		err_sys("Can't open %s", argv[1]);
	}

	while ((dirp = readdir(dp)) != NULL) {
		printf("name: %s, no: %ld\n", dirp->d_name, dirp->d_ino);
	}

	closedir(dp);

	exit(0);
}