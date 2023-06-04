#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>


#define MAX_BUF 1024

int main(int argc, char* argv[]) {
    if(argc!=2) {
        perror("too many arguments");
        return 1;
    }

    if(mkfifo(argv[1], 0666)== -1) {
        perror("error mkfifo");
        return 1;
    }
    //fd file descriptor
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror("error open");
        return 1;
    }
    char buf[MAX_BUF];
    
    while(1) {
        //serve per riempire il buffer sempre con una costante
        memset(buf, 0, sizeof(buf));
        int rd = read(fd, buf, sizeof(buf))>0;
        
        if(rd==-1){
            perror("error read");
            return 1;
        }
        else if(rd == 0){
            fd = open(argv[1], O_RDONLY);
             if(fd == -1) {
                perror("error open 2");
                return 1;
            }
        }
        else {   
            if(strcmp(buf, "FINE\n")==0) {
                break;
            }
            printf("%s", buf);
        }
    }
    remove(argv[1]);

    // soluzione flex
    /*
    while (1) {
        memset(buf, 0, sizeof(buf));
        int ret = read(fd, buf, sizeof(buf));
        if (ret == -1) {
            perror("read");
            return 1;
        } else if (ret == 0) {
            fd = open(argv[1], O_RDONLY);
            if (fd == -1) {
                perror("open2");
                return 1;
            }
        } else {
            printf("%s", buf);
            if (buf[ret - 1] == '\n') buf[ret - 1] = '\0';
            if (strcmp(buf, "FINE") == 0) {
                ret = unlink(argv[1]);
                if (ret == -1) {
                    perror("unlink");
                    return 1;
                }
                break;
            }
        }
    }
    */
    close(fd);
    return 0;
}