#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_SIZE 256

int main(int argc, char* argv[]) {
	// assumo venga passato un file.txt con due linee di testo
	if(argc!=2){
		perror("too many args");
		exit(1);
	}
	
	FILE* fl;
	if ((fl = fopen(argv[1], "r")) == NULL ) {
		perror("error open");
		exit(1);
	}
	
	char frCmd[MAX_SIZE];
	int curC;
	
	// fgets si ferma o quando finisce il file o quando finisce una riga
	while(fgets(frCmd, MAX_SIZE, fl)) {
		// lancia i comandi salvati in frCmd
		system(frCmd);
	}
	
	// maggiori spiegazioni su come prendere l'output del primo comando
	// http://www.microhowto.info/howto/capture_the_output_of_a_child_process_in_c.html
	
	return 0;
		 
}

