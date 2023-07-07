//15.25
#include <sys/timerfd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <stdlib.h>


#define max 1024

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("wrong number of arguments");
		return 0;
	}
	
	// Extract the tokens
	char input[max];
	strcpy(input, argv[1]);
    char *nIt, *periodC, *toprint;
    nIt = strtok(input, ",");
    periodC = strtok(NULL, ",");
	toprint = strtok(NULL, ",");
		
	int iters = atoi(nIt);
	double period = atof(periodC);
	
	printf("input: %d -- %f -- %s\n", iters, period, toprint);
	
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
	
	return 0;
}

// 17.22
