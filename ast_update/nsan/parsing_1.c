#include "minishell.h"


t_tokens *cmd_list(t_tokens **cmd_list, t_tokens *ref_ptr)
{
    printf("inside cmd_list\n");
    ft_lstadd_from_back(cmd_list, ref_ptr);
    printf("after listaddFromback\n");
    return (*cmd_list);
}

void parse_pipe(t_tokens **whole_list, t_ast *ast_node)
{
    t_tokens *ref_ptr = *whole_list;
   
    while (ref_ptr && ft_strncmp(ref_ptr->str, "|", 1))
    {
        //ast_node->left will be the branch of the main ast_pipe_node
        // if(ref_ptr && ref_ptr->tok_types == T_REDIRECT_IN && ref_ptr->next->tok_types == T_WORD)
        //     parse_cmd_redirections(ast_node->left, cmd_list, ref_ptr); //add the str keyword to the left-node of cmd, which is left-node of main ast-node
        if(ref_ptr && ref_ptr->tok_types == 0)
        {
            printf("%d", ref_ptr->tok_types);
            printf("inside parse pipe\n");
            //**cmd_linked_list;
            t_tokens *cmd_linked_list = malloc(sizeof(t_tokens)); //
            ((ast_node->left)->right)->cmd_linked_list = cmd_list(&cmd_linked_list, ref_ptr); //add the str keyword to the left-node of cmd, which is left-node of main ast-node
        }
        else
        {
            (ast_node->left)->left = NULL;
        }
        ref_ptr = ref_ptr->next;
    }
}

//second level node branched out from main-pipe-ast-node
// void parse_cmd_redirections(t_ast *cmd_ast_node, t_tokens *ref_ptr) 
// {
//     cmd_ast_node->left = parse_cmd();
// }

//second level node branched out from main-pipe-ast-node
// void parse_cmd_arguments(t_ast *cmd_ast_node, t_tokens *ref_ptr)
// {
//     cmd_ast_node->right = cmd_list(cmd_list, ref_ptr);
// }



