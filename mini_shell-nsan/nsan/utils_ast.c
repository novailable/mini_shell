#include "minishell.h"

t_ast *ast(t_tokens **whole_list)
{
	int i;
	t_ast *ast_node;
	t_tokens *current;
	int flag = 0;

	i = 0;
	
	current = *whole_list;
	ast_node = malloc(sizeof(t_ast));
	// ast_node = NULL;
	if(current == NULL)
		return NULL;
	while(current != NULL)
	{
		if(ft_strncmp(current->str, "|", 1) == 0)
		{
			flag = 1;
			return(parse_pipe(whole_list, ast_node), ast_node);
		}
		else if (ft_strncmp(current->str, ">>", 2) == 0){
			flag = 1;
			return(parse_redirect(whole_list, ast_node, 1), ast_node);
		}
		else if (ft_strncmp(current->str, "<<", 2) == 0){
			flag = 1;
			new_line_input(1, current->next->str);
		}
		else if(ft_strncmp(current->str, "<", 1) == 0)
		{
			flag = 1;
			return(parse_redirect(whole_list, ast_node, 0), ast_node);
		}
		else if (ft_strncmp(current->str, ">", 1) == 0){
			flag = 1;
			return(parse_redirect(whole_list, ast_node, 1), ast_node);
		}
		else
			flag = 0;
		current = current->next;
	}
	if(!flag)
	{
		ast_node = parse_cmd(ast_node, whole_list, NULL);
		return (ast_node);
	}
	return (ast_node);
}
