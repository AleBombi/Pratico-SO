#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    if (argc!=3) {
        perror("Insert the right no of elements (2) !");
        return -1;
    }
    FILE *fl1 = fopen(argv[1], "r"); // puntatore all'inizio del primo file
    FILE *fl2 = fopen(argv[2], "w"); // puntatore all'inizio del secondo file
    
    fseek(fl1, 0L, SEEK_END);
    long int sz = ftell(fl1); // posizione corrente del file, ovvero l'ultima posizione (in byte)

    if(fork()==0) { 
        //codice primo figlio
        fseek(fl1, 0L, SEEK_SET);
        while(ftell(fl1)!=(sz/2)) {
            fputc(fgetc(fl1), fl2);
        }
    }
    else {
        // codice del padre 
        if(fork()==0) {
            //codice secondo figlio
            fseek(fl1, sz/2, SEEK_SET); //fl1 punta a metà
            fseek(fl2, sz/2, SEEK_SET); //fl2 punta a metà
            int curChar;
            while(1) {
                curChar = fgetc(fl1);
                if(curChar == EOF) { //finché non è finito il file
                    break;
                }
                fputc(curChar, fl2);
            }
        } 
    }

    fclose(fl1);
    fclose(fl2);
    return 0;
}