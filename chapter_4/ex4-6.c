#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
	char *filePathFrom;
	char *filePathTo;
	int fdFrom, fdTo;
	int have_holes, byte_count, res, current_position;
	char buff[BUF_SIZE];
	struct stat st;


	if(argc !=3 || !argv[1] || !argv[2])
	{
		fprintf(stderr, "Usage: %s <source file path> <target file path>\n",
				argv[0]);
		exit(1);
	}
	filePathFrom = argv[1];
	filePathTo = argv[2];
	if((fdFrom = open(filePathFrom, O_RDWR)) < 0)
	{
		fprintf(stderr, "open path from error");
		exit(1);
	}
	
	if(fstat(fdFrom, &st) != 0)
		fprintf(stderr, "stat error");
	else {
		if(S_ISREG(st.st_mode) && st.st_size > 512 * st.st_blocks) {
			have_holes = 1;
			printf("%s is a sparse-block file!\n", filePathFrom);
		} else {
			have_holes = 0;
			printf("%s is not a sparse-block file!\n", filePathFrom);
		}
	}

	if((fdTo = open(filePathTo, O_RDWR|O_APPEND|O_CREAT|O_TRUNC, 0666)) < 0)
	{
		fprintf(stderr, "open path to error");
		exit(1);
	}
	
	memset(buff, '\0', BUF_SIZE);
	if((res = read(fdFrom, buff, BUF_SIZE)) < 0)
	{
		fprintf(stderr, "fdFrom read error");
		exit(1);
	}
	if(have_holes)
	{
		byte_count = 0;
		for(current_position = 0;current_position < res; current_position++)
		{
			if(buff[current_position] != 0)
			{
				buff[byte_count] = buff[current_position];
				byte_count++;
			}
		}
	} else 
		byte_count = res;

	if((res = write(fdTo, buff, byte_count)) < 0)
	{
		fprintf(stderr, "fdTo write error");
		exit(1);
	}

	close(fdFrom);
	close(fdTo);
}

