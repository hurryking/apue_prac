#include "apue.h"
#include <errno.h>

int
main(int argc, char const *argv[])
{
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	errno = EAGAIN;
	perror(argv[0]);

	exit(0);
}