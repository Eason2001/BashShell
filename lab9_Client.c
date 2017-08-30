#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <arpa/inet.h>

#define INTARYSIZE 50 // the maximum array size of the array to be send

int BACKLOG=2; 
static int cliSock;

int optimi_socket(int s);
void process_conn_clientTS(int s);
void sig_proccess(int signo);
void sig_pipe(int sign);

typedef struct
{
	int intAry[INTARYSIZE];
	int size;
	int sum;

}intAryStruct;

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr; 
    int err;


	if(argc != 3)
	{
        printf("Please refer to the usage below: \n");
        printf("usage: %s  <ServerIP> <ServerPORT>\n", argv[0]);
		return 0;

	};


    cliSock = socket(AF_INET, SOCK_STREAM, 0);
    if(cliSock < 0){
        printf("socket error\n");
        return -1;  
    };

    // optimizing socket: increasing the timeout of duration
    err = optimi_socket(cliSock);
    if (err < 0) {
      printf("Couldn't optimize setting for cliSock.)\n");
      return -1;
    };

   
    bzero(&server_addr, sizeof(server_addr));       
    server_addr.sin_family = AF_INET;               
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[2]));             
    
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr); 
    connect(cliSock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));

    process_conn_clientTS(cliSock); 
    close(cliSock);   
    printf("exit\n");
    exit(0);


}

// optimizing socket: increasing the timeout of duration
int optimi_socket(int s)
{
    int err=0;

    struct timeval timeo = {5, 0};  //second, usecond
    //sending timeout  
    err = setsockopt(s,SOL_SOCKET,SO_SNDTIMEO,&timeo,sizeof(timeo));  
    if (err < 0) {
      perror("Couldn't setsockopt(Send NetTimeout)");

      return -1;
    };

    //receiving timeout  
    err = setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,&timeo,sizeof(timeo));  
    if (err < 0) {
      perror("Couldn't setsockopt(Receive NetTimeout)");
      return -1;
    };

    return 0;
}

void process_conn_clientTS(int s)
{
    ssize_t size = 0;
    char sndBuffer[1024];  
    char revBuffer[1024];
    char enKey;      
    intAryStruct sndintAry;
    int count=0,tmpInput;

    signal(SIGINT, sig_proccess);    //sig_proccess
    signal(SIGPIPE, sig_pipe);   //sig_pipe
    signal(SIGHUP, SIG_IGN);   //sig_proccess
    signal(SIGQUIT, SIG_IGN);   //sig_proccess

    bzero(&sndintAry, sizeof(intAryStruct));
    bzero(sndBuffer, sizeof(sndBuffer));   
    bzero(revBuffer, sizeof(revBuffer));  


    for(;;){

    	printf("Please input the number of integers[EXIT:CTRL+C]: ");
    	scanf("%d", &count);

    	sndintAry.size=count;

    	printf("Input integer one by one follow by 'ENTER': ");	

    	sndintAry.sum=0;
    	for (int i = 0; i < count; ++i)
    	{
    		tmpInput=0;
    		//the tips will keep showing untill end user input a valid integer 
    		while(scanf("%d%c", &tmpInput, &enKey) != 2 || enKey != '\n')
    		{
    			printf("You didn't enter a valid integer, Please input it again: ");

    		};
    		sndintAry.intAry[i]=tmpInput;
    		sndintAry.sum=sndintAry.sum+sndintAry.intAry[i];
    	};

    	printf("Array sum: %d \n", sndintAry.sum);	
    	memcpy(sndBuffer, &sndintAry, sizeof(intAryStruct));
        write(s, sndBuffer, sizeof(sndBuffer));
        

        size = read(s, revBuffer, 1024);
        if (size < 0)
        {
            perror(" reading socket error ");
        };

        if(size == 0){
            perror("Server terminated prematurely\n");

        };


        memcpy(&sndintAry, revBuffer, sizeof(intAryStruct));
        printf("The sum of integers array is: %d \n", sndintAry.sum);

    }


}

void sig_proccess(int signo)
{
    printf("Catch a exit signal!\n");
    kill(0,SIGTERM);
    printf("the program will exit\n");
    exit(1);

}


void sig_pipe(int sign)
{
	//can be different from sig_process according to different requirement
    printf("Catch a SIGPIPE signal!\n");
    kill(0,SIGTERM);
    printf("the program will exit\n");
    exit(1);
    
}

