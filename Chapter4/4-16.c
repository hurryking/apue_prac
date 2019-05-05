#include "apue.h"
#include <fcntl.h>

int
main(void)
{
	if (open("tempfile", O_CREAT) < 0) {
		err_sys("open error");
	}

	if (unlink("tempfile") < 0) {
		err_sys("unlink error");
	}
	printf("file unlinked\n");

	sleep(10);
	printf("done\n");
	exit(0);
}