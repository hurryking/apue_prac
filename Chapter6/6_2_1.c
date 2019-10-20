#include "apue.h"
#include <pwd.h>

int
main(void)
{
	struct  passwd *ptr;
	
	if ((ptr = getpwnam("ningjin")) == NULL)
		err_sys("getpwname error");

	printf("pw_passwd = %s\n", ptr->pw_passwd == NULL || ptr->pw_passwd[0] == 0 ? "(null)" : ptr->pw_passwd);
	exit(0);
}