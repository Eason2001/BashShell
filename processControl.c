#include <stdio.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>  
#include <sys/wait.h> 

//Zhicheng Pan, 104639463


int main(int argc, char *argv[])
{
        // int i;
        void (*oldHandler1)(); //to save default handlers
        void (*oldHandler2)(); //for CTR-C and CTR-Z
        int parInt, chiInt, status, tmpInt;
        pid_t pid;

        oldHandler1=signal(SIGINT, SIG_IGN); //ignore CTR-C
        oldHandler2=signal(SIGTSTP, SIG_IGN); // ignore CTR-Z

              //filtering out incorrect inputs from end users
      if (argc != 3)
      {

        printf("Please refer to the usage: \n");
        printf("usage: ./processControl.out <a-number-for-parent:1-10> <a-number-for-child:1-10>\n");
        exit(1);    

      };

      //int atoi(const char *nptr);
        parInt=atoi(argv[1]);
        chiInt=atoi(argv[2]);


      if ( parInt<=0 || parInt >10 || chiInt<=0 || chiInt>10 )
      {
              /* code */
        // printf("%d  %d \n", parInt,chiInt);
        printf("Please refer to the usage: \n");
        printf("usage: ./processControl.out <a-number-for-parent:1-10> <a-number-for-child:1-10>\n");
        exit(1);    

      };

      pid=fork();

      if (pid<0)
      {
              /* code */
        perror("creating a new process problem ");
        exit(1);    


      }else if (pid==0)  //child process
      {
              /* code */
        if (parInt>chiInt)
        {
                /* code */
                for (int i = 0; i < chiInt; ++i)
                {
                        /* code */
                    printf("child  %d : I am the child process...\n", getpid( ));   
                    printf("child  %d : my pid =  %d, ppid = %d\n", getpid(), getpid(), getppid());
                    printf("child  %d : I have to live %d seconds. \n", getpid(), chiInt-i);
                    sleep(1);
                };


        }else if (parInt<chiInt)
        {
                /* code */
                for (int i = 0; i < chiInt; ++i)
                {
                        /* code */
                    printf("child  %d : I am the child process...\n", getpid( ));   
                    printf("child  %d : my pid =  %d, ppid = %d\n", getpid(), getpid(), getppid());
                    printf("child  %d : I have to live %d seconds. \n", getpid(), chiInt-i);
                    sleep(1);
                    tmpInt=getppid();
                    if (tmpInt==1)
                    {
                            /* code */
                        printf("child  %d : I am an orphan now... \n", getpid());

                    }

                };


        }else
        {

                for (int i = 0; i < chiInt; ++i)
                {
                        /* code */
                    printf("child  %d : I am the child process...\n", getpid( ));   
                    printf("child  %d : my pid =  %d, ppid = %d\n", getpid(), getpid(), getppid());
                    printf("child  %d : I have to live %d seconds. \n", getpid(), chiInt-i);
                    sleep(1);
                };


        }   

        printf("child process is  exited.\n");
        exit(0);


      }else    //parent process
      {


        if (parInt>chiInt)
        {
                /* code */
                for (int i = 0; i < parInt; ++i)
                {
                        /* code */
                   printf("parent %d : I am the parent process...\n", getpid());
                   printf("parent %d : my pid =  %d  \n", getpid(), getpid());
                   printf("parent %d : I have to live %d seconds. \n", getpid(), parInt-i);
                   sleep(1);        
                            /* code */
                        status=kill(pid,0);
                        //wait(&status);
                        if (WIFEXITED(status))
                        {
                                /* code */
                           printf("parent %d : my child process %d is dead. \n", getpid(), pid);

                        }

                   

                };


        }else if (parInt<chiInt)
        {
                /* code */
                for (int i = 0; i < parInt; ++i)
                {
                        /* code */
                   printf("parent %d : I am the parent process...\n", getpid());
                   printf("parent %d : my pid =  %d  \n", getpid(), getpid());
                   printf("parent %d : I have to live %d seconds. \n", getpid(), parInt-i);
                   sleep(1);

                };                              


        }else
        {

                for (int i = 0; i < parInt; ++i)
                {
                        /* code */
                   printf("parent %d : I am the parent process...\n", getpid());
                   printf("parent %d : my pid =  %d   \n", getpid(), getpid());
                   printf("parent %d : I have to live %d seconds. \n", getpid(), parInt-i);
                   sleep(1);

                };         

        }   

 
        printf("parent process is  exited.\n");


      };


        signal(SIGINT, oldHandler1); // restore default
        signal(SIGTSTP, oldHandler2); // restore default
        return 0;


}