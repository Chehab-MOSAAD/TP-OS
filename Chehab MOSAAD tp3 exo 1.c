#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

void Afiiche_inode (struct stat* Infos){
    char *type;
    if(S_ISREG(Infos ->st_mode)){
        type = "fichier ordinaire";
    }
    else if(S_ISDIR(Infos ->st_mode)){
        type = "répertoire";
    }
    else if(S_ISFIFO(Infos ->st_mode)){
        type = "fichier FIFO";
    }
    else if(S_ISCHR(Infos ->st_mode)){
        type = "periferique caractere";
    }
    else if(S_ISBLK(Infos ->st_mode)){
        type = "periferique bloc";
    }
    else if(S_ISLNK(Infos ->st_mode)){
        type = "lien symbolique";
    }
    else if(S_ISSOCK(Infos ->st_mode)){
        type = "socket";
    }

    printf("type: %s, Taille: %d octets, %s", type, Infos->st_size, ctime(Infos->st_atime));
}

int main(int argc, char*argv[]){
    struct stat Infos;

    if (lstat("test.c",%Infos)==-1){
        perror("echec stat");
        exit(1);
    }
    Affiche_inode(%Infos);
}
