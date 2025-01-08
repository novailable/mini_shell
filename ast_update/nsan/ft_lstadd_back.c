#include "minishell.h"

void	ft_lstadd_from_back(t_tokens **cmd_list, t_tokens *node)
{
	printf("inside lst-addfrom-back\n");
	if ((*cmd_list) == NULL)
	{
		printf("%s", (*cmd_list)->str);
		(ft_lstlast(*cmd_list))->next = node;
	}
	else
		*cmd_list = node;
	   // Debugging: Print the list
    printf("cmd_list contents:\n");
    t_tokens *temp = *cmd_list;
    while (temp)
    {
        printf("%s -> ", temp->str);
        temp = temp->next;
    }
    printf("NULL\n");
}

t_tokens	*ft_lstlast(t_tokens *node)
{
	printf("inside ft_lstlast\n");
	while (node && node->next)
		node = node->next;
	printf("inside ft_lstlast _2\n");
	return (node);
}

