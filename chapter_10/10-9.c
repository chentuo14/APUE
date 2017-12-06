#include "apue.h"
#include "10-8.c"

unsigned int sleep2(unsigned int);
static void sig_int(int);

int main(void)
{
	unsigned int uslept;

	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	uslept = sleep2(5);
	printf("sleep2 returned: %u\n", uslept);
	exit(0);
}

static void sig_int(int signo)
{
	int i,j;
	volatile int k;

	printf("\nsig_int starting\n");
	for(i=0;i<300000;i++)
		for(j=0;j<4000;j++)
			k += i*j;
	printf("sig_int finished\n");
}
