#include "minishell.h"

char **cmd_list(t_tokens **whole_list)
{
    t_tokens *current;
    t_tokens *temp;
    char **list_of_cmd;
    int i;
    int j;

    i = 0;
    j = -1;
    current = *whole_list;
    temp = *whole_list;
    while(ft_strncmp(current->str, "|", 1 )) //find the word counts to the pipe's left
    {
        i++;
        current = current->next;
    }
    list_of_cmd = malloc(sizeof(char *) * (i + 1));
    while(++j < i) //loop again to add to the cmd_list
    {
        list_of_cmd[j] = temp->str;
        temp = temp->next;
    }
    list_of_cmd[j] = NULL;
    return (list_of_cmd);
}

t_ast *parse_cmd(t_ast *ast_node, t_tokens **whole_list) //return the left node of the pipe
{
    int i = 0;
    ast_node->type = T_WORD;
    ast_node->cmd = cmd_list(whole_list);
    ast_node->left = NULL;
    ast_node->right = NULL;
    return (ast_node);
}

void parse_pipe(t_tokens **whole_list)
{
    t_ast *ast_node;
    ast_node = malloc(sizeof(t_ast));
    ast_node->type = T_PIPE;
    // printf("type of main pipe node: %d\n",  ast_node->type);
    ast_node->left = parse_cmd(ast_node, whole_list); //this will be the node of the cmd word
    // printf("type of left node: %d\n",  ast_node->left->type);
    // ast_node->right = ast();
}

// void parse_redirect(t_ast **whole_list)
// {
    // t_ast *ast_node;
    // ast_node = malloc(sizeof(t_ast);
    // ast_node = NULL;
// }