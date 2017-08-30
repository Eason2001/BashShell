#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

//Zhicheng Pan, 104639463

// Execute the command using this shell program. 
#define SHELL "/bin/bash"

int my_system (const char *command)
{
      int status;
      pid_t pid;

      //duplicate a new process to excute the shell command
      pid = fork ();
      if (pid == 0)
        {
          // This is the child process.  Execute the shell command. 
          execl(SHELL, SHELL, "-c", command, NULL);
          //if excel excutes faild, the following code will be excuted,
          //otherwise it will never be excuted.
          exit(EXIT_FAILURE);
        }
      else if (pid < 0)
        // The fork failed.  Report failure.  
        status = -1;
      else
        //This is the parent process.  Wait for the child to complete.
        if (waitpid(pid, &status, 0) != pid)
          status = -1;
      return status;
}


int main(int argc, char *argv[])
{
  

      int cmdByte=0, cmdSta;
      char bufCMD[100]={'\0'};

      //filtering out incorrect inputs from end users
      if (argc != 1)
      {

        printf("Please refer to the usage: \n");
        printf("usage: ./myshell.out \n");
        exit(1);    

      };

      
      //a while loop to read the input until read nothing
      while(1)
      { 

        //initializing the bufCMD array for inputting a new command line
        for (int i = 0; i < 100; ++i)
        {
          /* code */
          bufCMD[i]='\0';

        };

        //using Unix read/write system call
        write(STDOUT_FILENO, "Input a shell command line here[direct 'ENTER' to exit]#: ",sizeof("Input a shell command line here[direct 'ENTER' to exit]#: "));
        cmdByte=read(STDIN_FILENO, bufCMD, 100);

        //end user enter only ENTER key, program will exit
        if (cmdByte==1)
        {

          write(STDOUT_FILENO, "You select to exit and program will exit! \n",sizeof("You select to exit and program will exit! \n"));
          exit(0);

        };

        cmdSta=my_system(bufCMD);
        //excuting command error
        if (cmdSta==-1)
        {
            /* code */
          write(STDOUT_FILENO, "The shell command executes failed and program will exit! \n",sizeof("The shell command executes failed and program will exit! \n"));
          exit(1);

        }


      }


}
