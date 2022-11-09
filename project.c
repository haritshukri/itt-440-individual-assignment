#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(void)
{
	int pipefds[2];
	int number;
	int i;
	int flag = 0;

	if(pipe(pipefds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();

	if(pid != 0)
	{
		void sigint_handler(int sig);
		if(signal(SIGINT,sigint_handler) == SIG_ERR){
		perror("signal");
		exit(1);
	}

	printf("\nParent: Enter a  number:\n");
	scanf("%d",&number);
	int x;
	for( x = 0; x < 3; x++){
		sleep(2);
		printf("Determining..\n");
	}
	close(pipefds[0]);
	write(pipefds[1],&number,sizeof(number));
	exit(EXIT_SUCCESS);
}

if (pid == 0)
{
	wait(NULL);
	close(pipefds[1]);
	read(pipefds[0],&number,sizeof(number));

	for (i=2;i<=number/2;++i)
	{
		if(number % i==0)
		{
			flag =1;
			break;
		}
	}

	if(number==1)
	{
		printf("\nChild: 1 is not a prime number.\n");
	}

	else
	{
		if(flag==0)
		printf("\nChild: %d is a prime number.\n",number);

		else
		printf("\nChild: %d is not a prime number.\n",number);
	}

		close(pipefds[0]);
	}
	return EXIT_SUCCESS;
}

void sigint_handler(int sig)
{
	printf("Process terminated. Goodbye.\n");
}
