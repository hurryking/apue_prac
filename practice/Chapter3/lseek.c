#include "apue.h"

int
main(void)
{
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
		printf("Don't support seek\n");
	} else {
		printf("support seek\n");
	}
	return 0;
}