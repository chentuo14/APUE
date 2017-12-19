#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char msg = 'X';
	int i =0;
	if(argc >1)
		msg = argv[1][0];

	for(i=0;i<10;i++)
	{
		printf("%c", msg);
		fflush(stdout);
		sleep(rand()%3);
		printf("%c", msg);
		fflush(stdout);
		sleep(rand()%2);
	}
	sleep(10);
	printf("\n%d - finished\n", getpid());
	return 0;
}
