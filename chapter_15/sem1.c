#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semid = 0;

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
};

int set_semvalue()
{
	union semun sem_union;

	sem_union.val = 1;
	if(semctl(semid, 0, SETVAL, sem_union) == -1)
		return -1;	

	return 0;
}

void del_semvalue()
{
	union semun sem_union;

	if(semctl(semid, 0, IPC_RMID, sem_union) == -1)
		fprintf(stderr, "Failed to delete semaphore\n");
}

int P()
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	if(semop(semid, &sem_b, 1) == -1)
	{
		fprintf(stderr, "P() failed\n");
		return -1;
	}
	return 0;
}

int V()
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if(semop(semid, &sem_b, 1) == -1)
	{
		fprintf(stderr, "V() failed\n");
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char msg = 'X';
	int i=0;

	if(argc > 1 && !strcmp(argv[1], "0"))
	{
		/* first user sem */
		if(set_semvalue() == -1)
		{
			fprintf(stderr, "Failed to initialize semaphore\n");
			return -1;
		}
		msg = argv[1][0];
		sleep(2);
	}

	semid = semget((key_t)1234, 1, 0666|IPC_CREAT);
	if(semid == -1)
	{
		printf("semget error\n");
		return -1;
	}
	
	for(i=0;i<10;i++)
	{
		if(P() == -1)
			return -1;
		printf("%c", msg);
		fflush(stdout);
		sleep(rand()%3);
		printf("%c", msg);
		fflush(stdout);
		if(V() == -1)
			return -1;
		sleep(rand()%2);
	}
	sleep(5);
	printf("\n%d - finished\n", getpid());

	if(argc > 1)
		del_semvalue();

	return 0;
}
