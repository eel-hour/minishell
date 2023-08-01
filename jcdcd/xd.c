#include "minishell.h"


int ft_strlen(char *str)
{
    int i = 0;
    while (str[i++]);
    return (i);
}

void echo_redirect(char **str, char *ptr, int type)
{
    int fd;
    
    int i = 0;
    if (type == 1)
    {
        char *args[] = {"/bin/ls", NULL};
        fd = open(ptr, O_CREAT | O_WRONLY | O_TRUNC, 0777);
        dup2(fd, 1);
        close(fd);
        execve("/bin/ls", args, NULL);
    }
    if (type == 2)
    {
        fd = open(ptr, O_CREAT | O_WRONLY | O_APPEND, 0777);
        dup2(fd, 1);
        close(fd);
        while (str[i])
        {
            write(1, str[i], ft_strlen(str[i]));
            write(1, "\n", 1);
            i++;
        }
    }
}

int main()
{
    char *args[] = {"Yasmine stupid ass", "vanilla", "face", NULL};
    echo_redirect(args, "xd",  2);
}