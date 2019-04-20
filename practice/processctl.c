#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);

void sig_int(int signo)
{
	printf("interrupt sign: %d \n%%", signo);
}

int
main(int argc, char const *argv[])
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	printf("%% ");
	while(fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n') {
			buf[strlen(buf) - 1] = 0;
		}

		if ((pid = fork()) < 0) {
			err_sys("fork error");
		//子进程
		} else if (pid == 0) { 
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
		}

		if (pid = waitpid(pid, &status, 0) < 0) {
			err_sys("waitpid error");
		}
	}

	printf("%% ");

	exit(0);
}