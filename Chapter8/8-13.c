#include "apue.h"

static void charatime(char *);

int
main(void)
{
	pid_t pid;

	TELL_WAIT();

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	} else if (pid == 0)
	{
		charatime("output from child\n");
		TELL_PARENT(getppid());
	} else {
		WAIT_CHILD();
		charatime("output from parent\n");
		// TELL_CHILD(pid);
	}

	exit(0);
}

static void
charatime(char *str)
{
	char *ptr;
	int c;

	setbuf(stdout, NULL);
	for (ptr = str; (c = *ptr++) != 0;)
		putc(c, stdout);
}