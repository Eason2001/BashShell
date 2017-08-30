#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//Zhicheng Pan, 104639463

int main(int argc, char *argv[])
{
	int fd1, fd2;
	char buffer[100];
	long int n1;
	//defining the counters
	int spaCount=0, alphCount=0, digCount=0, puncCount=0, lowCount=0, upCount=0, othCount=0, vowCount=0,totCount;

	//filtering out incorrect inputs from end users
	if (argc != 3)
	{
        //printf("The number of input parameters is: %d \n", argc);		
        printf("Please refer to the usage: \n");
	    printf("usage: ./a.out <input_file_name> <output_file_name> \n");
		exit(1);		

	};

	//trying to open an existing file and create a new file, 
	//printing errors if encountering files open errors.
	if(((fd1 = open(argv[1], O_RDONLY)) == -1) ||
	  ((fd2 = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC,0700)) == -1))
	{
		perror("file problem ");
        printf("Please refer to the usage: \n");
	    printf("usage: ./a.out <input_file_name> <output_file_name> \n");
		exit(1);
	}

	//a while loop to read the input file until read nothing
	while((n1=read(fd1, buffer, 100)) > 0)
	{	
		//a for loop to process the characters that read from the input file
		for (int i = 0; i < n1; ++i)
		{
			//judging the character and counting them
			if (islower(buffer[i]))
			{

				lowCount=lowCount+1;
				if (buffer[i]=='a'||buffer[i]=='e'||buffer[i]=='i'||buffer[i]=='o'||buffer[i]=='u')
				{

					vowCount=vowCount+1;
				};
				//changing the lowercase letter to uppercase letter
				buffer[i]=buffer[i]-32;


			}
			else if (isupper(buffer[i]))
			{

				upCount=upCount+1;
				if (buffer[i]=='A'||buffer[i]=='E'||buffer[i]=='I'||buffer[i]=='O'||buffer[i]=='U')
				{

					vowCount=vowCount+1;
				}

			}
			else if (isspace(buffer[i]))
			{

				spaCount=spaCount+1;
			}
			else if (isdigit(buffer[i]))
			{

				digCount=digCount+1;
			}
			else if (ispunct(buffer[i]))
			{

				puncCount=puncCount+1;
			}
			else 
			{
				othCount=othCount+1;

			};
			
		}

		//I/O write error
		if(write(fd2, buffer, n1) != n1)
		{
			perror("writing problem ");
			exit(3);
		}

		//I/O read error
		// Case of an error exit from the loop
		if(n1 == -1)
		{
			perror("Reading problem ");
			exit(2);
		}


	}

		//caculating and printing out the statistics
		alphCount=lowCount+upCount;
		totCount=spaCount+alphCount+digCount+puncCount+othCount;

		printf("The statistic of this file is as below: \n");
		printf("----------------------------------------------------------------\n");
		printf("total number of characters: %d \n", totCount);
		printf("number of alphabet letters: %d \n", alphCount);
		printf("number of lowercase letters: %d \n", lowCount);
		printf("number of uppercase letters: %d \n", upCount);
		printf("number of digital number: %d \n", digCount);
		printf("number of space number: %d \n", spaCount);

		printf("number of punctuation letters: %d \n", puncCount);
		printf("number of other letters: %d \n", othCount);
		printf("number of VOWELS letters(a,e,i,o,u): %d \n", vowCount);		
		printf("----------------------------------------------------------------\n");
		printf("The %d lowercase letters have been transfered to uppercase letters,\n", lowCount);		
		//using Char pointer to output String
		printf("and they are stored in file: %s \n", argv[2]);

		//closing the files and exit
		close(fd1);
		close(fd2);
		exit(0);

}
