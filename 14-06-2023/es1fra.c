#include <sys/timerfd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[]){
	
	if(argc != 2){
		perror("Invalid Arguments numbher");
		exit(0);
	}
	
	int printTime;
	double alltime;
	double seconds;
	double nanoSeconds;
	char* string2print;
	
	
	// devo dividere l'argv[1] per prendere i vari parametri
	char* delim = ",";
	char* token = strtok(argv[1],delim);
	//primo input -> numero di stampe
	printTime = atoi(token);
	
	token = strtok(NULL, delim);
	
	//secondo input-> intervallo di tempo 
	alltime = strtod(token, NULL);
	
	
	seconds = (int) alltime;
	nanoSeconds = (int)((alltime - seconds) * 100000000);
	
	token = strtok(NULL, delim);
	
	// ultimo input -> stringa da salvare
	string2print = strdup(token);
	
	// ho tutti gli input, ora timerfd
	
	int tmfd = timerfd_create(CLOCK_REALTIME, 0);// forse da cambiare?
	
	struct itimerspec its;
	struct timespec tms;
	

	tms.tv_sec = (time_t)seconds;
	tms.tv_nsec = (long) nanoSeconds;
	
	its.it_interval = tms;
	
	its.it_value = tms;
	
	timerfd_settime(tmfd, 0, &its, NULL);

	uint64_t buf;
	
	for(int i = 0; i < printTime; i++){
	
		read(tmfd,&buf,sizeof(uint64_t));
		
		printf("%d.%d %s\n", i+1, (int) time(0), string2print);
	}
	
}

