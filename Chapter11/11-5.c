#include "apue.h"
#include <pthread.h>

pthread_t tid_tmp;

void
cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
}

void *
thr_fn1(void *arg)
{
	printf("开始清理线程　1\n");
	pthread_cleanup_push(cleanup, "线程1 第一个handler");
	pthread_cleanup_push(cleanup, "线程1 第二个handler");
	printf("thread 1 push complete\n");
	pthread_cancel(tid_tmp);
	sleep(2);
	if (arg)
		pthread_exit((void *)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)1);
}

void *
thr_fn2(void *arg)
{
	printf("开始清理线程　2\n");
	pthread_cleanup_push(cleanup, "线程2 第一个handler");
	pthread_cleanup_push(cleanup, "线程2 第二个handler");
	printf("thread 2 push complete\n");
	// tid_tmp = pthread_self();
	if (arg)
		return((void *)2);
		
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return((void *)2);
}

int
main(void)
{
	int err;
	pthread_t tid1,tid2;
	void *tret;

	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	if (err != 0)
		err_exit(err, "can't create thread 1");
	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
	tid_tmp = tid2;
	if (err != 0)
		err_exit(err, "can't create thread 2");

	err = pthread_join(tid1, &tret);
	if (err != 0)
		err_exit(err, "can't join with thread 1");
	printf("thread 1 exit code %ld\n", (long)tret);
	err = pthread_join(tid2, &tret);
	if (err != 0)
		err_exit(err, "can't join with thread 2");
	printf("thread 2 exit code %ld\n", (long)tret);
	exit(0);
}