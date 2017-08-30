#include <fcntl.h> // This is the client
#include <stdio.h>
#include <unistd.h>
#include <string.h>  //strlen  bzero 
#include <stdlib.h>

#define PUBLIC_FIFO "/tmp/Group5"
#define groupID  "Group_5"
#define lastName  "PAN"
#define firstName "ZHICHENG"
#define UWinID    "104639463"


int main(int argc, char *argv[]){ // Client
	char ch[50], msg[300], cwdPath[150];
	int fd, offset=0;
	pid_t pid;
	char newline='\n';

	while((fd=open(PUBLIC_FIFO, O_WRONLY))==-1){
	fprintf(stderr, "trying to connect\n");
	sleep(1);
	};


    bzero(msg, sizeof(msg));   
	pid = getpid();
	// "PID, CWD, Last Name, First Name, UWinID\n"

    sprintf(msg, "%d", pid);
    offset=strlen(msg);

    strcpy(msg+offset, ", ");
    offset=offset+strlen(", ");
    
    getcwd(cwdPath, sizeof(cwdPath));
    strcpy(msg+offset, cwdPath);
	offset=offset+strlen(cwdPath);

    strcpy(msg+offset, ", ");
    offset=offset+strlen(", ");

    strcpy(msg+offset, groupID);
	offset=offset+strlen(groupID);

    strcpy(msg+offset, ", ");
    offset=offset+strlen(", ");

    strcpy(msg+offset, lastName);
	offset=offset+strlen(lastName);
    strcpy(msg+offset, ", ");
    offset=offset+strlen(", ");

    strcpy(msg+offset, firstName);
	offset=offset+strlen(firstName);
    strcpy(msg+offset, ", ");
    offset=offset+strlen(", ");

    strcpy(msg+offset, UWinID);
	offset=offset+strlen(UWinID);

	write(fd, msg, strlen(msg));
	write(fd, &newline, 1);
	close(fd);

    printf("We just send a message blew to the server: \n");
    printf("%s \n", msg);

	close(fd);

}