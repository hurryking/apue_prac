#include <stdio.h>
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *
getpwnam(const char *name)
{
	struct passwd *ptr;

	// rewind to head of pwd
	setpwent();

	while ((ptr = getpwent()) != NULL)
	{
		if (strcmp(name, ptr->pw_name) == 0)
		{
			break;
		}
	}

	endpwent();
	return (ptr);
}

int
main(int argc, char const *argv[])
{
	char *name;
	struct passwd *ptr;
	name = "root";
	ptr = getpwnam(name);
	printf("%d\n", ptr->pw_uid);
	return 0;
}