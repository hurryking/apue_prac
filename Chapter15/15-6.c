#include "apue.h"
#include <sys/wait.h>

#define DEF_PAGER "/bin/more"

int
main(int argc, char * argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char *pager, *argv0;
	char line[MAXLINE];
	FILE *fp;

	if (argc != 2)
		err_quit("usage: %s <pathname>", argv[0]);

	if ((fp = fopen(argv[1], "r")) == NULL)
		err_sys("can't open %s", argv[1]);
	
	if (pipe(fd) < 0)
		err_sys("pipe error");

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	} else if (pid > 0)
	{
		/* 关闭读 */
		close(fd[0]);

		/* 读fp 写到父进程的写端 */
		while (fgets(line, MAXLINE, fp) != NULL)
		{
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				err_sys("write error to pipe");

		}

		if (ferror(fp))
			err_sys("fgets error");

		close(fd[1]); /* fp读完了　关闭管道的写端 */

		if (waitpid(pid, NULL, 0) < 0)
		{
			err_sys("waitpid error");
		}

		exit(0);
	} else
	{
		close(fd[1]); /* 关闭管道写端 */
		if (fd[0] != STDIN_FILENO)
		{
			/* 复制子进程的标准输入描述符　*/
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
			{
				err_sys("dup2 error to stdin");
			}
			close(fd[0]);
		}

		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;

		/*　取 /bin/more　中的more */
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;
		else
			argv0 = pager;

		if (execl(pager, argv0, (char *)0) < 0)
			err_sys("execl error for %s", pager);
	}

	exit(0);
}