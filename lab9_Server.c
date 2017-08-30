#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>   //socket, setsockop
#include <unistd.h>
#include <netinet/in.h>   //struct sockaddr_in
#include <netinet/tcp.h>  //TCP_NODELAY
#include <signal.h>
#include <errno.h>        //errno != EINTR
#include <string.h>
#include <arpa/inet.h> //inet_ntop
#include <time.h>


//created by Group 5: 
//Zhicheng Pan(104639463)
//Xiaoliang Duan(104506882)
//Yunpeng Bai(104462928)
//Chao Zhang(104656305)
//Rui Wang(104491717) 


int GetProfileString(char * profile, char * AppName, char * KeyName, char * KeyVal );
void sig_proccess(int signo);
void sig_pipe(int sign);
void process_conn_server(int s);
int optimi_socket(int s);



#define cfgFile "Server.config" //default configuration file
#define BUFFSIZE 1024
#define INTARYSIZE 50 // the maximum array size of the array to be send
#define CONLINELENGTH 100   //the maximum length of a line in configuration file

char SERVERIP[30]={0};       
int SERVERPORT=18888;       
int BACKLOG=2; 

typedef struct
{
	int intAry[INTARYSIZE];
	int size;
	int sum;

}intAryStruct;


int main(int argc, char *argv[])
{
    char tmpStr[30]={0}; //used to load parameters from Server.config


    printf("Initializing the server ... ...\n");

    printf("Setting the signal process\n");
    signal(SIGINT, sig_proccess);    //sig_proccess
    signal(SIGPIPE, sig_pipe);   //sig_pipe
    signal(SIGHUP, SIG_IGN);   //sig_proccess
    signal(SIGQUIT, SIG_IGN);   //sig_proccess

    //loading the configuration from configuration file
    printf("loading parameters from file: %s \n",cfgFile);
    memset(tmpStr, 0, sizeof(char)*30);
    if(GetProfileString(cfgFile,"[Local_Server.config]","Local_Server_IP",tmpStr))
    {
        perror("loading parameters from Server.config error");
        exit(1);
    };
    if(strlen(tmpStr)!=0)
        strcpy(SERVERIP,tmpStr);
    printf("The server IP: %s \n", SERVERIP);

    memset(tmpStr, 0, sizeof(char)*30);
    if(GetProfileString(cfgFile,"[Local_Server.config]","Local_Server_Port",tmpStr))
    {
        perror("loading parameters from Server.config error");
        exit(1);
    };
    if(strlen(tmpStr)!=0)
    SERVERPORT = atoi(tmpStr);
    printf("The service port: %d \n", SERVERPORT);


    //creating socket for listening 
    int serSock,cliSock, tcpFlag, err;      
    struct sockaddr_in server_addr; 
    struct sockaddr_in client_addr;     
    char client_name[INET_ADDRSTRLEN];
    pid_t pid;  

    printf("creating the socket for listening ...\n"); 
 
    //UPD:SOCK_DGRAM   TCP:SOCK_STREAM
    serSock = socket(AF_INET, SOCK_STREAM, 0);
    if(serSock < 0){
        perror("socket error");
        return -1;  
    };

    err = optimi_socket(serSock);
    if (err < 0) {
      perror("Couldn't optimize setting for serSock.)");
      return -1;
    };

    bzero(&server_addr, sizeof(server_addr));   
    server_addr.sin_family = AF_INET;           
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVERPORT);         


    err = bind(serSock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(err < 0){
        perror("bind error");
        return -1;
    }

    //listening on the port
    err = listen(serSock, BACKLOG);
    if(err < 0){
        perror("listen error");
        return -1;  
    }



    socklen_t addrlen = sizeof(client_addr);
    printf("the server is waiting on prot: %d \n", SERVERPORT); 

 
    for(;;) 
    {

        cliSock = accept(serSock, (struct sockaddr*)&client_addr, &addrlen);
        printf("got a Client: \n"); 

        if(cliSock < 0){     
            close(cliSock); 
            continue;   
        };

        err = optimi_socket(cliSock);
        if (err < 0) {
          perror("Couldn't optimize setting for cliSock.)");
          return -1;
        };


        if(inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,client_name,sizeof(client_name)) == NULL)
        {
            printf("Unable to get client address!\n",stderr);
            close(cliSock); 
            continue;  

        };

        // logging the transaction of the server
        FILE *fp;
        fp = fopen("server.log", "a+");
        if(fp == 0)
        {
            printf("Cannot open the server log file.\n");
            exit(0);
        }
        fseek(fp, 0, SEEK_END);
        fprintf(fp, "A client request from: %s, port: %d.  ", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        time_t timep;
        time(&timep);
        fwrite(ctime(&timep), strlen(ctime(&timep)), 1, fp);
        fclose(fp);


        pid = fork();       
        if( pid == 0 )  
        {     
            close(serSock);      
            process_conn_server(cliSock);
            return 0;

            
        }else if ( pid > 0 ) 
        {

            close(cliSock);  
        }else 
        {
             perror("fork process error");   
        }


    }




}

void process_conn_server(int s)
{
    ssize_t size = 0;
    char sndBuffer[1024];  
    char revBuffer[1024];     
    intAryStruct revintAry;

    usleep(100000); 
    for(;;){

        bzero(sndBuffer, sizeof(sndBuffer));   
        bzero(revBuffer, sizeof(revBuffer));         
        
        size = read(s, revBuffer, sizeof(revBuffer));

        if (size == -1)
        {

            usleep(100000); 
            continue;

        };

        //Client close socket
        if (size == 0)
        { 
            // usleep(100000);
            close(s);
            printf("client exit!\n");
            break; 
        };



        if (size > 100)
        {
            bzero(&revintAry,sizeof(intAryStruct));
            memcpy(&revintAry, revBuffer, sizeof(intAryStruct));

            printf("got a request from a client: \n");
            printf("the size of this integer array is: %d \n", revintAry.size); 

            // logging the transaction of the server
            FILE *fp;
            fp = fopen("server.log", "a+");
            if(fp == 0)
            {
                printf("Cannot open the log file.\n");
                exit(0);
            }
            fseek(fp, 0, SEEK_END);


            printf("the integer list is below: \n");
            fprintf(fp, " integers list is:");

            revintAry.sum=0;
            for (int i = 0; i < revintAry.size; ++i)
            {

            	printf("%d ", revintAry.intAry[i]);
                fprintf(fp, " %d", revintAry.intAry[i]);
            	revintAry.sum=revintAry.sum+revintAry.intAry[i];

            };

            fprintf(fp, "\t");
            fprintf(fp, "sum of this integers list: ");
            fprintf(fp, "%d", revintAry.sum);
            fprintf(fp, "\n\n");
            fclose(fp);


            memcpy(sndBuffer,&revintAry,sizeof(intAryStruct)+1);
            write(s, sndBuffer, sizeof(intAryStruct));

        };


    }   



}




int GetProfileString(char * profile, char * AppName, char * KeyName, char * KeyVal )
{
    char aname[30],kname[30];
    char buf[CONLINELENGTH],*c;
    FILE *fp;
    int found=0;
    if( (fp=fopen( profile,"r" ))==NULL )
    {
        printf( "openfile [%s] error [%s]\n",
        profile,strerror(errno));
        return(-1);
    };
    fseek( fp, 0, SEEK_SET );
    sprintf( aname,"%s", AppName );
    memset( kname, 0, sizeof(kname) );
    while( !feof(fp) && fgets( buf,CONLINELENGTH,fp )!=NULL )
    {

        if( found==0 )
        {
            if( buf[0]!='[' )
            {
                continue;
            }
            else if ( strncmp(buf,aname,strlen(aname))==0 )
            {
                found=1;
                continue;
            }
        }
        else if( found==1 )
        {
        if( buf[0]=='#' )
        {
            continue;
        }
        else if ( buf[0]=='[' )
        {
            break;
        }
        else
        {
            if( (c=(char*)strchr(buf,'='))==NULL )
                continue;
            memset( kname, 0, sizeof(kname) );
            sscanf( buf, "%[^=]", kname );
            if( strcmp(kname, KeyName)==0 )
                {
                    sscanf( ++c, "%[^\r]", KeyVal);
                    found=2;
                    break;
                }
            else
                {
                    continue;
                }
            }
        }
    }
    fclose( fp );
    if( found==2 )
    return(0);
    else
    return(-1);

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




