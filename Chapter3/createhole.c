#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghijklmnopqistuvwxyz";
char buf2[] = "ABCDEFGHIJKLMNOPQISTUVWXYZ";

int
main(void)
{
	int fd;

	if ((fd = creat("file.hole", FILE_MODE)) < 0) {
		err_sys("create error");
	}

	if (write(fd, buf1, 26) != 26) {
		err_sys("buf1 write error");
	}

	if (lseek(fd, 16384, SEEK_SET) == -1) {
		err_sys("lseek error");
	}

	if (write(fd, buf2, 26) != 26) {
		err_sys("buf2 write error");
	}

	exit(0);
}