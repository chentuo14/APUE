#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>

#define TEXT_SIZE 512

struct msgbuf {
	long mtype;
	char mtext[TEXT_SIZE];
};

int main(int argc, char *argv[])
{
	int msqid;
	pid_t pid;
	struct msgbuf msg;

	msqid = msgget(IPC_PRIVATE, IPC_CREAT|0666);
	if(msqid == -1)
	{
		printf("create msg queue failed!\n");
		return -1;
	}

	pid = fork();
	if(pid < 0) {
		printf("fork failed!\n");
		return -1;
	} else if(pid == 0) {		/* child */
		msgrcv(msqid, &msg, sizeof(msg), 1, IPC_NOWAIT);
		printf("child: msg.mtext is %s\n", msg.mtext);
		strcpy(msg.mtext, "Hello, too!");
		msgsnd(msqid, &msg, sizeof(msg), IPC_NOWAIT);
	} else {					/* parent */
		msg.mtype = 1;
		strcpy(msg.mtext, "Hello!");
		msgsnd(msqid, &msg, sizeof(msg), IPC_NOWAIT);
		sleep(2);
		msgrcv(msqid, &msg, sizeof(msg), 1, IPC_NOWAIT);
		printf("parent:msg.mtext is %s\n", msg.mtext);
	}
	return 0;
}
