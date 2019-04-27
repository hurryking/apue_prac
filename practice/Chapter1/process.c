#include "apue.h"

int
main(int argc, char const *argv[])
{
	printf("hello from %ld\n", (long)getpid());
	exit(0);
}