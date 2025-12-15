#include "../include/pipex.h"

void    exit_handler(void)
{
    ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
    exit (0);
}

int open_file(char  *file, int is_parent)
{
    int output;

    if (is_parent == 0)
        output = open(file, O_RDONLY, 0777);
    if (is_parent == 1)
        output = opne(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (output == -1)
        exit(0);
    return (output);
}

void    ft_free_tab(char **tab)
{
    size_t i;

    i = 0;
    while (tab[i])
            free(tab[i++]);
    free(tab);
}

char    *ft_getenv(char *name, char **env)
{
    int     i;
    int     j;
    char    *sub;

    i = 0;
    while (env[i])
    {
        j = 0;
        while (env[i][j] && env[i][j] != '=')
            j++;
        sub = ft_substr(env[i], 0 ,j);
        if (ft_strcmp(sub, name) == 0)
        {
            free(sub);
            return (env[i] + j + 1);
        }
        free(sub);
        i++;
    }
    return NULL;
}

char    *get_path(char *cmd, char **env)
{
    int     i;
    char    *exec;
    char    **allpath;
    char    *path_part;
    char    **s_cmd;

    i = 0;
    allpath = ft_split(ft_getenv("PATH", env), ':');
    s_cmd = ft_split(cmd, ' ');
    while (allpath[i])
    {
        path_part = ft_strjoin(allpath[i], "/");
        exec = ft_strjoin(path_part, s_cmd[0]);
        free(path_part);
        if (access(exec, F_OK | X_OK) == 0)
        {
            ft_free_tab(s_cmd);
            return (exec);
        }
        free (exec);
    }
    ft_free_tab(allpath);
    ft_free_tab(s_cmd);
    return (cmd);
}

