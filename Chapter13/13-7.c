#include "apue.h"
#include <pthread.h>
#include <syslog.h>

sigset_t mask;

extern int already_running(void);

void 
reread(void)
{

}

void *
thr_fn(void *arg)
{
	int err, signo;

	for(;;)
	{
		err = sigwait(&mask, &signo);
		if (err != 0)
		{
			syslog(LOG_ERR, "sigwait failed\n");
			exit(1);
		}

		switch(signo)
		{
			case SIGHUP:
				syslog(LOG_INFO, "Re-reading configuration file\n");
				reread();
				break;
			case SIGTERM:
				syslog(LOG_INFO, "got SIGTERM; exiting\n");
				exit(0);
			default:
				syslog(LOG_INFO, "unexpected signal %d\n", signo);
		}
	}

	return(0);
}

int
main(int argc, char *argv[])
{
	int err;
	pthread_t tid;
	struct sigaction sa;
	char *cmd;

	if ((cmd = strrchr(argv[0], '/')) == NULL)
	{
		cmd = argv[0];
	} else
	{
		cmd++;
	}
    
	/*　变成守护进程　*/
	daemonize(cmd);

	/*　确定只有一个守护进程的副本在跑 */
	if (already_running())
	{
		syslog(LOG_ERR, "daemon alread running");
		exit(1);
	}

	/* 屏蔽除了 SIGHUP 以外的所有信号　*/
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: can't restore SIGHUP default");

	sigfillset(&mask);
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
	{
		err_exit(err, "SIG_BLOCK error");
	}

	/*
	 * 创建一个县城去处理 SIGHUP 和　SIGTERM
	 */
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if (err != 0)
	{
		err_exit(err, "can't create thread");
	}


	return(0);
}