#include "apue.h"
#include <fcntl.h>

int
main(int argc, char const *argv[])
{
	int status;
	if (argc != 2) {
		err_sys("usage: fcntl <descriptor#>");
	}

	if ((status = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
		err_sys("fcntl error for fd %d", atoi(argv[1]));
	}

	switch(status & O_ACCMODE) {
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
		default:
			printf("unkown access mode\n");
	}

	if (status & O_APPEND) {
		printf(", append");
	}
	if (status & O_NONBLOCK) {
		printf(", nonblocking");
	}
	if (status & O_SYNC) {
		printf(", synchronous writes");
	}

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if (val & O_FSYNC) {
		printf(", synchronous & writes");
	}
#endif
	putchar('\n');
	exit(0);
}