#include "apue.h"

int globval = 6;
char buf[] = "a write to stdout\n";

int
main(void)
{
	int var;
	pid_t pid;
	
	var = 88;
	// if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
	// 	err_sys("write error");
	printf("%s\n", buf);
	printf("before fork\n");

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	} else if (pid == 0)
	{
		globval++;
		var++;
	} else
	{
		sleep(2);
	}

	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globval, var);
	exit(0);
}
