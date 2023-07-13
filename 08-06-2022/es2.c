#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

void invertiLink(char*, char*);
void inverti(char*);

int main(int argc, char* argv[]){
	
	if(argc != 2) {
		printf("not the right numeber of arguments");
	}
	
	// argv[1] indica il path del file in input
	char *path = argv[1];

	// prendo le informazioni sull'argomento passato
	struct stat statBuf;
	
	if (lstat(path, &statBuf)!=0) {
		printf("lstat error");
		exit(1);
	}
	
	// verifico che sia un soft link
	if (S_ISLNK(statBuf.st_mode)) {
		inverti(path);
	} 	
	// verifico che sia una directory
	else if (S_ISDIR(statBuf.st_mode)) {
		
		char* dirPath = realpath(path, NULL);
		DIR* dir = opendir(dirPath);
		struct dirent *entry;
		
		while( (entry = readdir(dir)) != NULL) {
		
			if (entry->d_type == DT_LNK) {
				char tmpPath[PATH_MAX];
				memset(tmpPath, 0, PATH_MAX);
				snprintf(tmpPath, PATH_MAX, "%s/%s", dirPath, entry->d_name);
				inverti(tmpPath);
			}	
		} 		
	}
	return 0;
}

void inverti(char* sflink) {

	char *absPath = realpath(sflink, NULL);
	if (absPath == NULL){
		printf("realpath error\n");
		return;
	}
	invertiLink(sflink, absPath);
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

