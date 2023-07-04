#include <sys/types.h>
#include <dirent.h>
#include <dirent.h>
#include <stdio.h>
#include <libgen.h>
#include <string.h>
#define MAXPATH 1024

void printFile(char *s, int lvl){
	for(int i=0; i<lvl; i++){
		printf("\t");
	}
	printf("%s\n", s);
}

void printTree(char* path, int lvl) {
	DIR* dir = opendir(path);
	if (dir == NULL) {
		printf("cannot open %s\n", path);
		return;
	}
	
	struct dirent *obj;
	while( (obj = readdir(dir)) != NULL) {
		if( strncmp(obj->d_name, ".", 1) == 0) {
			continue;
		}
		printFile(obj->d_name, lvl);
		
		if(obj->d_type == DT_DIR) {
			char buffer[MAXPATH];
			snprintf(buffer, MAXPATH, "%s/%s", path, obj->d_name);
			printTree(buffer, lvl+1);		
		}	
	}
}

int main(int argc, char* argv[]) {
	
	if(argc != 2) {
		perror("too many arguments");
	}
	
	printTree(argv[1], 0);
	return 0;
}
