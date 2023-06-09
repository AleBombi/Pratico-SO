#include <sys/stat.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

void invertiLink(char*, char*);

int main(int argc, char* argv[]){
	
	if(argc != 2) {
		perror("not the right numeber of arguments");
	}
	// argv[1] indica il path del file in input
	char *pathArg = argv[1];

	// prendo il realpath del file puntato usando realpath()
	char absPath[256];
	realpath(argv[2], absPath);
	if (absPath==NULL) {
		perror("error realpath");
		exit(1);
	}

	// prendo le informazioni sull'argomento passato
	struct stat statBuf;
	if (lstat(pathArg, statBuf)!=0) {
		perror("lstat error");
		exit(1);
	}

	// verifico che sia un soft link
	if (S_ISLNK(statBuf.st_mode) == 0) {
		perror("the argument isn't a soft link");
		exit(1);
	} 
	
	invertiLink(pathArg, absPath);

}

void invertiLink(char* pathSoftLink, char* pathActualFile) {
// da sistemare, ma l'idea c'è

	// duplico la stringa
	char* pathPadreSL = strdup(pathSoftL);
	dirname(pathPadreSL)

	char* pathPadreAF = strdup( pathActualFile);
	
	// sposto il file soft link nella dir del file puntato
	if(rename(pathSoftLink, strcat(basename(pathActualFile),pathPadreSL))!=0) {
		perror("rename error");
	}
	
	// sposto il file puntato originalmente nella dir del softlink
	if(rename(pathActualFile, strcat(basename(pathSoftLink),pathPadreAF))!=0) {
		perror("rename error");
	}

}

