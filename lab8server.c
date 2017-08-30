#include <sys/wait.h> 
#include <fcntl.h> // This is the server
#include <stdio.h>
#include <unistd.h> //unlink
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>    // for exit
#include <string.h>  //strlen

#define LOGGING_FILE "lab8.log"
#define PUBLIC_FIFO "/tmp/Group5"

void logging(char *msg);

int main(int argc, char *argv[]){
	int fd, status;
	char msg[300];

	unlink(PUBLIC_FIFO);
	if(mkfifo(PUBLIC_FIFO, 0777)){
		perror("Creating PUBLIC_FIFO file error");
		return 1;
	}
	chmod(PUBLIC_FIFO, 0777);

	//if the logging file does not exist, create a new one
	if((fd = open(LOGGING_FILE, O_RDONLY)) == -1)
	{
		fd = open(LOGGING_FILE, O_CREAT|O_WRONLY|O_TRUNC,0700);
		printf("Creating a new logging file. \n");

	}else
	{
		printf("Using existed logging file. \n");

	};
	close(fd);

	while(1){
		fprintf(stderr, "Waiting for a client.\n");
		fd = open(PUBLIC_FIFO, O_RDONLY);
		fprintf(stderr, "Got a client: ");
		bzero(msg, sizeof(msg)); 
		read(fd, &msg, sizeof(msg));
		fprintf(stderr, "%s\n", msg);

		if(fork()==0){
			close(fd);
			logging(msg);
		}else

		waitpid(0, &status, WNOHANG);

	}

}

void logging(char *msg){
	char newline='\n';
	char msg2[300];
	int fd;

    strcpy(msg2, msg);
    // printf("%s \n", msg2);

	if((fd = open(LOGGING_FILE, O_WRONLY|O_APPEND,0700)) == -1)
	{
		perror("open logging file problem");
		exit(1);
	};

	write(fd, msg2, strlen(msg2));
	write(fd, &newline, 1);

	close(fd);
	exit(0);

}
