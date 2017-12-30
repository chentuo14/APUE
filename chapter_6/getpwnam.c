#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	char *username = "pi";
	struct passwd *my_info;
	my_info = getpwnam(username);
	if(!my_info)
	{
		perror("getpwnam error");
		exit(1);
	}

	printf("my name = [%s]\n", my_info->pw_name);
	printf("my passwd = [%s]\n", my_info->pw_passwd);
	printf("my uid = [%d]\n", my_info->pw_uid);
	printf("my gid = [%d]\n", my_info->pw_gid);
	printf("my gecos = [%s]\n", my_info->pw_gecos);
	printf("my dir = [%s]\n", my_info->pw_dir);
	printf("my shell = [%s]\n", my_info->pw_shell);

	return 0;
}

