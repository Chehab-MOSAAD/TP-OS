#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void ouvrirRep(){
    DIR *Repertoire;
    struct dirent *Element;
    struct stat Infos;

    Repertoire = opendir(".");

    if (Repertoire==NULL){
        perror(".");
        exit( -1);
    }

    while ((Element = readdir(Repertoire))!=NULL){
        printf("%-20s :",Element->d_name);

        stat(Element->d_name,&Infos);

        if(S_ISREG(Infos.st_mode)){
            printf("fichier     ");
        }
        else if(S_ISDIR(Infos.st_mode)){
            printf("répertoire  ");
        }
        else if(S_ISFIFO(Infos.st_mode)){
            printf("fichier FIFO");
        }
        else if(S_ISCHR(Infos.st_mode)){
            printf("caractere   ");
        }
        else if(S_ISBLK(Infos.st_mode)){
            printf("bloc        ");
        }
        else if(S_ISLNK(Infos.st_mode)){
            printf("lien        ");
        }
        else if(S_ISSOCK(Infos.st_mode)){
            printf("socket      ");
        }

        printf("%8ld octets ",Infos.st_size);
        printf("%s",ctime(&Infos.st_mtime));

    }
    closedir(Repertoire);
}

int main(int argc, char* argv[]){
    struct stat Infos;
    if (argc <= 1){
        ouvrirRep();
    }
    else{
        for (int i = 1; i < argc; i++){
            printf("%-20s :",argv[i]);

            stat(argv[i],&Infos);

        if(S_ISREG(Infos.st_mode)){
            printf("fichier     ");
        }
        else if(S_ISDIR(Infos.st_mode)){
            printf("répertoire  ");
        }
        else if(S_ISFIFO(Infos.st_mode)){
            printf("fichier FIFO");
        }
        else if(S_ISCHR(Infos.st_mode)){
            printf("caractere   ");
        }
        else if(S_ISBLK(Infos.st_mode)){
            printf("bloc        ");
        }
        else if(S_ISLNK(Infos.st_mode)){
            printf("lien        ");
        }
        else if(S_ISSOCK(Infos.st_mode)){
            printf("socket      ");
        }

        printf("%8ld octets ",Infos.st_size);
        printf("%s",ctime(&Infos.st_mtime));
        }
    }

    exit(0);
}
