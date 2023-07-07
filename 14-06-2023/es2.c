//17.35
#include <sys/timerfd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <stdlib.h>


#define max 1024

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("wrong number of arguments");
		return 0;
	}
	
	// Extract the tokens
	char input[max];
    char *nIt[argc-1], *periodC[argc-1], *toprint[argc-1];
    char *token;
    
    int iters[argc-1];
    double period[argc-1];
    
    for (int i=0; i<argc-1; i++){ 
    	strcpy(input, argv[i+1]);
    	
		token = strtok(input, ",");
		
		nIt[i] = strtok(NULL, ",");
		periodC[i] = strtok(NULL, ",");
		toprint[i] = strtok(NULL, ",");
		
		iters[i] = atoi(nIt[i]);
		period[i] = atof(periodC[i]);
		
		token = NULL;
		printf("input: %d -- %f -- %s\n", iters[i], period[i], toprint[i]);
	}
	
	/*
	
	int fdC = timerfd_create(1, CLOCK_REALTIME);
	if(fdC == -1) {
		printf("timerfd_create error");
	}
	// set the interval time
	struct itimerspec newit;
	newit.it_value.tv_sec = period;
	newit.it_value.tv_nsec = 0;
	newit.it_interval.tv_sec = period;
	newit.it_interval.tv_nsec = 0;
	
	if(fdC>0) {
		for (int i=1; i<=iters; i++) {
			timerfd_settime(fdC, 0, &newit, NULL);
			
			fd_set rfds;
			int retval;
			
			FD_ZERO(&rfds);
			FD_SET(0, &rfds);
			FD_SET(fdC, &rfds);
			
			retval=select(fdC+1, &rfds, NULL, NULL, NULL);
			
			printf("%d. %d %s\n", i, (int)time(NULL), toprint);	
		}
	}
	*/
	return 0;
}


