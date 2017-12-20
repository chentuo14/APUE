#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[8];
	int age;
}people;

int main(int argc, char *argv[])
{
	int shmid;
	people *p_map;
	key_t key;
	char pathname[30];
	int i = 0;

	strcpy(pathname, "/tmp");
	key = ftok(pathname, 0x03);
	if(key == -1)
	{
		perror("ftok error\n");
		return -1;
	}
	printf("key=%d\n", key);
	shmid = shmget(key, 0, 0);
	if(shmid == -1)
	{
		perror("shmread:shmget error\n");
		return -1;
	}
	printf("shmid=%d\n",shmid);
	p_map = (people*)shmat(shmid, NULL, 0);
	for(i=0;i<3;i++)
	{
		printf("name:%s\n", (*(p_map+i)).name);
		printf("age:%d\n", (*(p_map+i)).age);
	}
	if(shmdt(p_map) == -1)
	{
		perror("shmdt error\n");
		return -1;
	}
	return 0;
}



