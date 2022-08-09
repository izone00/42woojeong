#include <stdio.h>//perror
#include <string.h>//strerror
#include <unistd.h>//access

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
// extern int errno;
extern char **environ;

int main(int argc, char *argv[])
{
    char    filename[20] = "/bin/";
    char    **av;

    strcat(filename, argv[1]);
    strcat(filename, ".exe");
    printf("%s\n", filename);
    av = malloc(sizeof(char *) * 2);
    av[0] = argv[1];
    av[1] = NULL;
    printf("%s\n", av[0]);
    execve(filename, av, environ);
    perror("err");
}