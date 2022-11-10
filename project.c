#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(void){
	int pipefds[2];
	char message[20];
	int i;

	if (pipe(pipefds)== -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	} 

	pid_t pid = fork();

	if(pid != 0){
		void sigint_handler(int sig);
		if(signal(SIGINT, sigint_handler)== SIG_ERR){
			perror("signal");
			exit(1);
		}

		printf("\nParent: Enter message: \n");
		scanf("%s", message);
		int x;
		for(x = 0; x < 3; x++){
			sleep(1);
			printf("Receiving..\n");
		}

		close(pipefds[0]);
		write(pipefds[1], &message, sizeof(message));
		exit(EXIT_SUCCESS);
	}

	if(pid == 0){
		wait(NULL);
		close(pipefds[1]);
		read(pipefds[0], &message, sizeof(message));
		printf("\nChild: Your message is %s\n", message);
		close(pipefds[0]);
	}

	return EXIT_SUCCESS;
}

void sigint_handler(int sig){
	printf("Process terminated. Do not disturb!\n");
}
