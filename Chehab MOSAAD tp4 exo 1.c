#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 4

int TPF[2];
int i = 1;
int retour_fils;

void pere(){
    close(TPF[0]);
    while(i<=N){
        write(TPF[1], (void*)&i, sizeof(int));
        sleep(1);
        i++:
    }
    close(TPF[1]);
    wait(&retour_fils);
    printf("[Pere] Mon fils %d est termine avec le code %d. \n", retour_fils>>8, WEXITSTATUS(retour_fils));
}

void fils(){
    close TPF[1];
    int octets;
    while ((octets = read(TPF[0], (void*)&i, sizeof(i)))>0){
        printf("[Fils] %d \n", i);
    }
    close(TPF[0]);
}

int main(int argc, char *argv[]){
    pid_t pid;
    int retour_fils;
    pipe(TPF);
    if(pipe(TPF)==-1){
        perror("Erreur pipe");
        exit(1);
    }

    pid = fork();
    switch(pid){
    case -1:
        perror("Erreur fork");
        exit(2);
    case 0:
        fils();
        exit(1);
    default:
        pere();
        exit(0);
    }
    return 0;
}

void occurence(){
   char c;
   char ch;
   int occurrence = 0;
   int fichier;

   fichier = open(FICHE, O_RDONLY, 0);
    if (fichier == -1){
        perror("Erreur Creation !");
        exit(2);
    }

    printf("Entrez un caractère: ");
    scanf("%c",&c);

    while (!feof(fichier)) {
        ch = fgetc(fichier);
        if(ch == c){
            ++occurrence;
       } while (ch != EOF);
    }

    if (fgetc(fichier) == -1){
        perror("Erreur lire !");
        exit(1);
    }

    close(fichier);
   printf("Le nombre d’occurrence de %c est %d", c, occurrence);
   exit(0);
}
