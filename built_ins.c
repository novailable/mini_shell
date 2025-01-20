#include "minishell.h"

// void cd_built_in()
// {
//     char *cwd = getcwd(NULL, 0);
//     printf("%s\n", cwd);
// }

void ft_built_ins(char **list_of_cmd) //whole cmd list --> [[echo], [hi]]
{
    int i = -1;;
    while(list_of_cmd[++i])
    {
        if(ft_strncmp(list_of_cmd[i], "echo", 4) == 0)
        {
            if(ft_strncmp(list_of_cmd[i+1], "-n", 2) == 0)
            {
                printf("%s\n", list_of_cmd[i + 2]);
                break;
            }
            else
                printf("%s", list_of_cmd[i + 1]);
        }
        if(ft_strncmp(list_of_cmd[i], "cd", 2) == 0)
        {
            if(chdir(list_of_cmd[i+1]) == -1)
                printf("bash: cd: %s No such file or directory\n", list_of_cmd[i+1]);
        }
    }
}