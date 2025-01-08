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
	printf("inside the ast\n");
	if(current == NULL)
		return NULL;
	if(ft_strncmp(current->str, "|", 1))
	{
		printf("inside strcmp ast\n");
		parse_pipe(whole_list, ast_node);
	}
	return (ast_node);
}
