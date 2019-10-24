#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
	pid_t pid;

	printf("oirginal process, pid = %ld\n", (long)getpid());

	if ((pid = fork()) < 0) 
	{
		err_sys("fork error");
	} else if (pid == 0) 
	{
		if ((pid = fork()) < 0) 
			err_sys("fork error");
		else if (pid > 0) 
			exit(0);

		sleep(2);
		printf("second child, parent pid = %ld\n", (long)getppid());
		exit(0);
	}

	if (waitpid(pid, NULL, 0) != pid)
		err_sys("waitpid error");
	else
		printf("waited pid = %d\n", pid);

	exit(0);
}