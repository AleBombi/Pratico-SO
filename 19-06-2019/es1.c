// inzio 16:34

#include <sys/prctl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	/*
	int* status;

	prctl(PR_SET_CHILD_SUBREAPER, 0, 0, 0, 0);
	
	printf("\n\npid del nonno: %d", getpid());
	printf("\nppid del nonno: %d", getppid());

	if( fork() == 0 ) {
		
		
		if ( fork() == 0) {
			// codice nipote
			int p=1;
			prctl(PR_GET_CHILD_SUBREAPER, &p);
			printf("\n\npid del nipote: %d", getpid());
			printf("\nppid del nipote: %d", getppid());
			printf("\n\nnipote exit");
			exit(1);
			
		}
		else{
			// codice figlio
			printf("\n\npid del figlio: %d", getpid());
			printf("\nppid del figlio: %d", getppid());
			sleep(2);
			int p=1;
			prctl(PR_GET_CHILD_SUBREAPER, &p);
			printf("\n\figlio exit");
			exit(1);
		}
	}
	else {
		// codice nonno
		wait(status);
		printf("\n\npid del nonno: %d", getpid());
		printf("\nppid del nonno: %d", getppid());
		printf("\nnonno exit");
		exit(0);
		
	}
	*/
	
    int *status;
    int i=0;

    prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0);
    printf("nonno: %d :  ppid: %d\n", getpid(), getppid());
    if(fork() != 0)
    {
        while(1)
        {
            wait(status);
            if(++i == 2)
            {
                break;
            }
        }
        int p = 1;
        prctl(PR_GET_CHILD_SUBREAPER, &p);
        printf("PARENT : %d\n",p);
        printf("PARENT Exiting\n");
    }
    else
    {
        printf("Before CHILD: %d: my dad  %d\n",getpid(), getppid());
        if(fork() == 0)
        {
            int p = 1;
            printf("Before grandchild: %d: my dad %d\n",getpid(), getppid());
            sleep(2);
            printf("After grandchild: %d: my dad %d\n",getpid(), getppid());
            prctl(PR_GET_CHILD_SUBREAPER, &p);
            printf("After grandchild : %d\n",p);
            printf("Grandchild Exiting\n");
            exit(0);
        }
        else
        {
            int p = 1;
            prctl(PR_GET_CHILD_SUBREAPER, &p);
            printf("After CHILD : %d\n",p);
            printf("After CHILD: %d: my dad  %d\n",getpid(), getppid());
            printf("CHILD Exiting\n");
            exit(1);
        }
    }   
    return 0;


}

