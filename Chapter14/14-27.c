#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYINCR (1024*1024*1024)

int
main(int argc, char * argv[])
{
	int fdin, fdout;
	void *src, *dst;
	size_t copysz;
	struct stat sbuf;
	off_t fsz = 0;

	if (argc != 3)
		err_quit("usage: %s <fromfile> <tofile>", argv[0]);

	if ((fdin = open(argv[1], O_RDONLY)) < 0)
		err_sys("can't open %s for reading", argv[1]);

	if ((fdout = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0)
		err_sys("can't create %s for writing", argv[2]);

	/* 统计输入文件的长度 */
	if (fstat(fdin, &sbuf) < 0)
		err_sys("fstat failed");

	/* 设置输出文件的大小 */
	if (ftruncate(fdout, sbuf.st_size) < 0)
		err_sys("ftruncate error");

	while (fsz < sbuf.st_size)
	{
		/* 要拷贝的内容大于1G就先拷贝1G 切片 */
		if ((sbuf.st_size -fsz) > COPYINCR)
		{
			copysz = COPYINCR;
		} else
		{
			copysz = sbuf.st_size -fsz;
		}

		if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED)
		{
			err_sys("mmap err for input");
		}

		if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz)) == MAP_FAILED)
		{
			err_sys("mmap err for output");
		}
		close(fdin);
		close(fdout);

		/* 复制内存映射区的内容 */
		memcpy(dst, src, copysz);
		munmap(src, copysz);
		munmap(dst, copysz);
		fsz += copysz;
	}
	exit(0);
}