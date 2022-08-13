#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t my_pid = getpid();
    printf("%d\n", (int)my_pid);
    return (0);
}