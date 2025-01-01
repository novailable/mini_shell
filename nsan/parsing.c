#include "minishell.h"

char **cmd_list(t_tokens **whole_list, t_tokens **ref_ptr)
{
    t_tokens *current;
    t_tokens *temp;
    char **list_of_cmd;
    int i;
    int j;

    current = *whole_list;
    temp = *whole_list;
    i = 0;
    j = -1;

    while (current && current != *ref_ptr) {
        i++;
        current = current->next;
    }
    list_of_cmd = malloc(sizeof(char *) * (i + 1));
    while (++j < i) {
        list_of_cmd[j] = temp->str;
        temp = temp->next;
    }
    list_of_cmd[j] = NULL;
    *whole_list = current;
    return (list_of_cmd);
}


t_ast *parse_cmd(t_ast *ast_node, t_tokens **whole_list, t_tokens *ref_ptr) //return the left node of the pipe
{
    int i = 0;
    ast_node->type = T_WORD;
    ast_node->cmd = cmd_list(whole_list, &ref_ptr);
    while(ast_node->cmd[i] != NULL)
    {
        printf("%s\n", ast_node->cmd[i]);
        i++;
    }
    ast_node->left = NULL;
    ast_node->right = NULL;
    return (ast_node);
}

void parse_pipe(t_tokens **whole_list)
{
    t_ast *ast_node;
    t_tokens *ref_ptr = *whole_list;

    while (ref_ptr && ft_strncmp(ref_ptr->str, "|", 1))
        ref_ptr = ref_ptr->next;
    ast_node = malloc(sizeof(t_ast));
    ast_node->type = T_PIPE;
    ast_node->left = parse_cmd(ast_node, whole_list, ref_ptr);
    if (*whole_list && ft_strncmp((*whole_list)->str, "|", 1) == 0)
        *whole_list = (*whole_list)->next;
    ast_node->right = ast(whole_list);
}


void parse_redirect(t_tokens **whole_list, int flag)
{
    t_ast *ast_node;
    t_tokens *ref_ptr;

    ref_ptr = *whole_list;
    while (ref_ptr && (ft_strncmp(ref_ptr->str, "<", 1) && ft_strncmp(ref_ptr->str, ">", 1)))
        ref_ptr = ref_ptr->next;
    ast_node = malloc(sizeof(t_ast));
    // ast_node->type = T_REDIRECT_OUT;
    ast_node->left = parse_cmd(ast_node, whole_list, ref_ptr);
    if(*whole_list && flag == 0 && ft_strncmp((*whole_list)->str, "<", 1) == 0)
    {
        *whole_list = (*whole_list)->next;
        ast_node->right = ast(whole_list);
    }
    else if(*whole_list && flag == 1 && ft_strncmp((*whole_list)->str, ">", 1) == 0)
    {
        *whole_list = (*whole_list)->next;
        ast_node->out_file = (*whole_list)->str;
        printf("Redirect to output file: %s\n", ast_node->out_file);
    }
    else
    {
        fprintf(stderr, "Syntax error: Missing file after '>'\n");
        free(ast_node);
        return;
    }
}
