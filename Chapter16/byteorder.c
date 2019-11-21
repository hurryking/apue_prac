#include "apue.h"
#include <inttypes.h>

int
main(void)
{
	uint32_t i = 0x04030201;
	unsigned char *cp = (unsigned char *)&i;

	printf("%d %d %d %d\n", cp[0], cp[1], cp[2], cp[3]);
	if (*cp == 1)
		printf("little-endian\n");
	else if (*cp == 4)
		printf("big-endian\n");
	else
		printf("who knows\n");
	exit(0);
}