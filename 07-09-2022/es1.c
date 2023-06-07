#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) { 

	char* arguments[argc];  
	// per convenzione arguments deve contenere anche il comando
	for(int i=1; i<argc; i++) {
		arguments[i-1]=argv[i];
	}
	arguments[argc-1] = NULL;
	// l'ultimo elemento deve essere null
	
	char pathComando[256] = "/usr/bin/";

	strcat(pathComando, argv[1]);
	
	while(1) {
		clock_t start = clock();
		if(fork()==0) {
			if( execv(pathComando, arguments) == -1) {
				perror("error execv");
				exit(1);
			}
		}
		else {
			wait(NULL);
			start = clock() - start;
                        double time = (double) start / CLOCKS_PER_SEC;
			if (time <= 1 ) exit(0);
		}
	}
    return 0;
}
