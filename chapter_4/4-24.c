#include "apue.h"
#include "../chapter_2/2-16.c"

int main(void)
{
	char *ptr;
	size_t size;
	if(chdir("/var/spool/anacron") < 0)
		err_sys("chdir failed");
	ptr = path_alloc(&size);
	if(getcwd(ptr, size) == NULL)
		err_sys("getcwd failed");
	printf("cwd= %s\n", ptr);
	exit(0);
}
