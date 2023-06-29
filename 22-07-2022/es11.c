#include <sys/types.h>
#include <dirent.h>
#include <dirent.h>
#include <stdio.h>
#include <libgen.h>

int main(int argc, char* argv[]) {
	
	if(argc != 1) {
		perror("too many arguments");
	}
	
	DIR* dir; 
	if ( (dir = opendir(argv[0])) == NULL ) {
		perror("the dir doesn't exist");
	}
	struct dirent *obj;
	char *name;
	while( (obj = readdir(dir)) != NULL) {
		//printf("%s\n", obj->d_name);
		name = basename(obj->d_name);
		printf("%s\n", name);
	}
}
