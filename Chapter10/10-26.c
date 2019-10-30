#include "apue.h"

static void
sig_int(int signo)
{
	printf("cautch SIGINT\n");
}

static void
sig_chld(int signo)
{
	printf("cautch SIGCHLD\n");
}

int
main(void)
{
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");

	if (signal(SIGCHLD, sig_chld) == SIG_ERR)
		err_sys("signal(SIGCHLD) error");

	if (system("/bin/ed") < 0)
		err_sys("system() error");
	
	exit(0);
}