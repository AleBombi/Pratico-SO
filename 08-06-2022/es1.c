#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

void invertiLink(char*, char*);

int main(int argc, char* argv[]){
	
	if(argc != 2) {
		printf("not the right numeber of arguments");
	}
	
	// argv[1] indica il path del file in input
	char *pathArg = argv[1];


	// prendo le informazioni sull'argomento passato
	struct stat statBuf;
	if (lstat(pathArg, &statBuf)!=0) {
		printf("lstat error");
		exit(1);
	}

	// verifico che sia un soft link
	if (!S_ISLNK(statBuf.st_mode)) {
		printf("the argument isn't a soft link");
		exit(1);
	} 

	// prendo il realpath del file puntato usando realpath()
	char *absPath = realpath(pathArg, NULL);
	
	if (absPath==NULL) {
		printf("error realpath");
		exit(1);
	}
	

	invertiLink(pathArg, absPath);

	return 0;

}

void invertiLink(char* pathSl, char* pathAf) {

	// variabili per Sl
	char* tmpSl = strdup(pathSl);
	char* dirOfSl = dirname(tmpSl);
	tmpSl = strdup(pathSl);
	char* nameSl = basename(tmpSl);

	// variabili per Af
	char* tmpAf = strdup(pathAf);
	char* dirOfAf = dirname(tmpAf);
	tmpAf = strdup(pathAf);
	char* nameAf = basename(tmpAf);

	char newPathAf[PATH_MAX];
	memset(newPathAf, 0, PATH_MAX);
	snprintf(newPathAf, PATH_MAX, "%s/%s", dirOfSl, nameAf);
	
	char newPathSl[PATH_MAX];
	memset(newPathSl, 0, PATH_MAX);
	snprintf(newPathSl, PATH_MAX,"%s/%s", dirOfAf, nameSl);
	
	
	// sposto il file puntato originalmente nella dir del softlink
	if(rename(pathAf, newPathAf)!=0) {
		printf("rename error");
		exit(1);
	}
	// creo il symbolic link chiamato newPathSl che punta al realPath di newPathAf
	symlink(realpath(newPathAf, NULL), newPathSl);
	
	remove(pathSl);
	
}

