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

int afficher (const char* FICHE){
    int fichier, lire, ecrit;
    char TAB [512];

    fichier = open(FICHE, O_RDONLY, 0);
    if (fichier == -1){
        perror("Erreur Creation !");
        exit(2);
    }
    ecrit = 0;
    lire = 0;
    while ((lire == ecrit) && (lire = read(fichier, TAB, 512)>0)){
        ecrit = write(1, TAB, lire);
    }

    if (ecrit == -1){
        perror("Erreur lire !");
        exit(1);
    }
    close(fichier);
}

int fonction_fils (char * argv){
    int source = open(argv, O_RDONLY);
    afficher(argv);
    close(source);
    exit(0);
}

int my_cat(int argc, int nb_max, char * argv[]){
    if (strcmp(argv[argc -1], ">")){
        int destination = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWUSR);
        dup2(destination,1);
        nb_max = argc-2;
    }

    for (int i = 1; i < nb_max; i++){
        pid_t pid = fork();
        switch(pid){
        case -1:
            perror("Erreur Creation Fils!");
            return -1;
        case 0 :
            fonction_fils(argv[1]);
        default:
            break;
        }
    }
}
