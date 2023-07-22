#include "minishell.h"

int pipeee(char *const *commad_one, char *const *commad_two, int first, int fd_last_time)
{
    
    int fd[2];
    int pid1;
    int pid2;
    // printf()
    if (pipe(fd) == -1)
        return 1;
    //firstime
    if (first)
    {
        pid1 = fork();
        if (pid1 < 0)
            return 2;
        if (pid1 == 0)
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execve(commad_one[0], commad_one, NULL);
        }
    }
    //
    if (!first)
        fd[0] = fd_last_time;
    //
    pid2 = fork();
    if (pid2 < 0)
    {
        return 3;
    }
    if (pid2 == 0)
    {
        // if (!first)
        //     dup2(fd[1], STDOUT_FILENO);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve(commad_two[0], commad_two,  NULL);
    }
    // close(fd[0]);
    close(fd[1]);

    if (first)
        waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return (fd[0]);
}

int main()
{
    char *const commad_one [100] = {"/sbin/ping","-c","5","google.com"};
    char *const commad_two [100] = {"/usr/bin/grep" , "bytes"};
    char *const commad_tree [100] = {"/usr/bin/wc" , "-l"};



    int fd[2];
    if (pipe(fd) == -1)
        return 1;

    int pid1 = fork();
    if (pid1 < 0)
        return 2;
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve(commad_one[0], commad_one, NULL);
    }

    pipeee(commad_one, commad_two, 0, fd[0]);
    // int pid2 = fork();
    // if (pid2 < 0)
    // {
    //     return 3;
    // }
    // if (pid2 == 0)
    // {
    //     dup2(fd[0], STDIN_FILENO);
    //     close(fd[0]);
    //     close(fd[1]);
    //     execve(commad_two[0], commad_two,  NULL);
    // }
    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    // waitpid(pid2, NULL, 0);
    // return 0;
}


// pipe(s1, s2);