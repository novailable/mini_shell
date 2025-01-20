#include "minishell.h"


char **parse_cmd(char ***args_list, t_tokens **whole_list, int flag)
{
	int i;

	i = 0;
	t_tokens *current = *whole_list;
	while(current && current->tok_types != T_PIPE)
	{
		if(flag)
		{
			if(current->tok_types == T_WORD)
			{
				(*args_list)[i] = ft_strdup(current->str);
				i++;
			}
			else if(current->tok_types == T_REDIRECT_OUT || current->tok_types == T_REDIRECT_IN || current->tok_types == T_APPEND)
				current = current->next;
		}
		else if(!flag)
		{
			if(current->tok_types == T_REDIRECT_OUT || current->tok_types == T_REDIRECT_IN || current->tok_types == T_APPEND)
			{
				(*args_list)[i] = ft_strdup(current->str);
				if(current->next->tok_types == T_WORD)
				{
					i++;
					(*args_list)[i] = ft_strdup(current->next->str);
					i++;
					current = current->next;
				}
			}
		}
		current = current->next;
	}
	(*args_list)[i] = NULL;
	return (*args_list);
}

t_ast *cmd_node_branch(t_tokens *current)
{
	t_ast	*cmd_node;
	t_ast	*cmd_left_node;
	t_ast	*cmd_right_node;

	cmd_node = malloc(sizeof(t_ast));
	cmd_left_node = malloc(sizeof(t_ast));
	cmd_right_node = malloc(sizeof(t_ast));
	if (!cmd_node || !cmd_left_node || !cmd_right_node)
	{
		printf("Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	cmd_node->left = redirection_list(cmd_left_node, &current);
	cmd_node->right = args_list(cmd_right_node, &current);

	/*debug statement for left and right nodes of cmd_list*/
	char **right_node_char = (cmd_node->right)->cmd;
	 char **left_node_char = (cmd_node->left)->cmd;
	if(right_node_char != NULL)
	{
		while(*right_node_char)
		{
			printf("cmd_RIGHT_node_cmd: %s\n", *right_node_char);
			right_node_char++;
		}
	}
	if(left_node_char != NULL)
	{
	    while(*left_node_char)
	    {
	        printf("cmd_LEFT_node_cmd: %s\n", *left_node_char);
	        left_node_char++;
	    }
	}
	return (cmd_node);
}

 /*debug statement for left and right nodes of cmd_list*/
	// char **right_node_char = (cmd_node->right)->cmd;
	//  char **left_node_char = (cmd_node->left)->cmd;
	// while(*right_node_char)
	// {
	//     printf("cmd_RIGHT_node_cmd: %s\n", *right_node_char);
	//     right_node_char++;
	// }
	// if(left_node_char != NULL)
	// {
	//     while(*left_node_char)
	//     {
	//         printf("cmd_LEFT_node_cmd: %s\n", *left_node_char);
	//         left_node_char++;
	//     }
	// }