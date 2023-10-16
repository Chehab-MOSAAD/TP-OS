#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAXBASSIN 5

int Remplire[2];
int Etat[2];
int n_fois = 0;
// char val;
int num = 1;

void pere()
{
    close(Remplire[0]);
    close(Etat[1]);

    // le processus père sait qu’il va jouer N fois
    for (int i = 0; i < n_fois; i++)
    {
        // printf("processus de pid %d : ping\n",getpid());

        write(Remplire[1], &num, sizeof(int));

        if (read(Etat[0], &num, sizeof(int)) == -1)
        {
            perror("error lire fils");
            exit(96);
        }
    }

    close(Remplire[1]);
    close(Etat[0]);
}

void fils()
{
    close(Remplire[1]);
    close(Etat[0]);

    int bassin = 0;
    int return_read = 0;

    while ((return_read = read(Remplire[0], &num, sizeof(char))))
    {
        if (num > 0)
        {
            printf("*");
            fflush(stdout);
            bassin++;
            if (bassin < MAXBASSIN)
            {
                write(Etat[1], &bassin, sizeof(int));
            }


        }
        else
        {
            printf("\n");
            bassin = 0;
            write(Etat[1], &bassin, sizeof(int));
        }
    }

    if (return_read == -1)
    {
        perror("error lire fils");
        exit(96);
    }

    close(Remplire[0]);
    close(Etat[1]);
    exit(1);
}

int main(int argc, char **argv)
{
    int f_flags;
    f_flags = fcntl(Etat[0], F_GETFL); /* R ́ecup ́eration des flags */
    f_flags |= O_NONBLOCK;
    fcntl(Etat[0], F_SETFL, f_flags);

    if (argc < 2)
    {
        perror("Usage");
        exit(100);
    }

    n_fois = atoi(argv[1]);

    if (pipe(Remplire) == -1)
    {
        perror("probleme creation tube pere");
        exit(99);
    }

    if (pipe(Etat) == -1)
    {
        perror("probleme creation tube fils");
        exit(98);
    }

    switch (fork())
    {
    case -1:
        perror("probleme creation processus fils");
        exit(97);
        break;
    case 0:
        fils();
        break;

    default:
        break;
    }

    pere();
    // printf("fin ping\n");
    // printf("fin pong\n");
    return 0;
}
