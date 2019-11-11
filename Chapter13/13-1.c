#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void
daemonize(const char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	/*文件屏蔽字*/
	umask(0);

	/* 文件描述符的最大数量 */
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		err_quit("%s: can't get file limit", cmd);

	/* 成为　会话首进程使其失去控制终端 */
	if ((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if (pid != 0)
		exit(0);
	setsid();

	/*　确定将来不会重新分配终端　*/
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: can't ignore SIGHUP", cmd);

	if ((pid = fork()) < 0)
		err_quit("%s: can't fork");
	else if (pid != 0)
		exit(0);

	/*　修改当前工作目录为根目录 防止文件系统不能被卸载 */
	if (chdir("/") < 0)
		err_quit("%s: can't change directory to /", cmd);

	/* 关闭所有打开的文件描述符 */
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;

	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	/*把 0 1 2 文件描述符　重定向到 /dev/null */
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 !=0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
}