#include "apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

#define NTHR 4				/* 参与排序的线程数 */
#define NUMNUM 8000000L		/* 需要排序的数据总量 */
#define TNUM (NUMNUM/NTHR) 	/* 每个线程需要排序的数量 */

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;

#ifdef SOLARIS
#define heapsort qsort;
#else
extern int heapsort(void *, size_t, size_t, int (*)(const void *, const void *));
#endif

int
complong(const void *arg1, const void *arg2)
{
	long l1 = *(long *)arg1;
	long l2 = *(long *)arg2;

	if (l1 == l2)
		return 0;
	else if (l1 < l2)
		return -1;
	else
		return 1;
}

/*
 * 排序的工作线程
 */
void *
thr_fn(void *arg)
{
	long idx = (long)arg;
	heapsort(&nums[idx], TNUM, sizeof(long), complong);
	pthread_barrier_wait(&b);

	return((void *)0);
}

/*
 * 合并每个线程的排序结果
 */
void merge()
{
	long idx[NTHR];
	long i, minidx, sidx, num;

	for (i = 0; i < NTHR; i++)
		idx[i] = i * TNUM;

	for (sidx = 0;sidx < NUMNUM; sidx++)
	{
		num = LONG_MAX;
		for (i = 0; i < NTHR; i++)
		{
			if ((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num))
			{
				num = nums[idx[i]];
				minidx = i;
			}
		}
		snums[sidx] = nums[idx[minidx]];
		idx[minidx]++;
	}
}

int main()
{
	unsigned long i;
	struct timeval start,end;
	long long startusec,endusec;
	double elapsed;
	int err;
	pthread_t tid;

	/*
	 * 初始化数据集
	 */
	srandom(1);
	for (i = 0; i < NUMNUM; i++)
	{
		nums[i] = random();
	}

	/*
	 * 创建8个线程 排序数字
	 */
	gettimeofday(&start, NULL);
	pthread_barrier_init(&b, NULL, NTHR+1);
	for (i = 0; i < NTHR; i++)
	{
		err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
		if (err != 0)
			err_exit(err, "can't create thread");
	}
	pthread_barrier_wait(&b);
	merge();
	gettimeofday(&end, NULL);

	startusec = start.tv_sec * 1000000 + start.tv_usec;
	endusec = end.tv_sec * 1000000 + end.tv_usec;
	elapsed = (double)(endusec - startusec) / 1000000.0;
	printf("sort tool %.4f seconds\n", elapsed);
	for ( i = 0; i < NUMNUM; i++)
		printf("%ld\n", snums[i]);

	return(0);
}