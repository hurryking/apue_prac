#include "apue.h"

int
main(void)
{
	char *ptr;
	size_t size;

	if (chdir("/var/spool/mail") < 0)
		err_sys("chdir failed");

	ptr = path_alloc(&size); //申请内存的函数　专门针对文件路径 符合 posix　标准
	if (getcwd(ptr, size) == NULL)
		err_sys("getpwd failed");

	printf("cwd = %s\n", ptr);
	exit(0);
}