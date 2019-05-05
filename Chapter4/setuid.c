#include "apue.h"

int
main(int argc, char const *argv[])
{
	printf("uid=%d, gid=%d, euid=%d, egid=%d\n", getuid(), getgid(), geteuid(), getegid());
	exit(0);
}