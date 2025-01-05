// int main() {
// 	struct sigaction sa_int;
// 	char **dest;
// 	t_tokens tokens;

// 	while(1)
// 	{
// 		// signal(SIGINT, handle_signal);
// 		sa_int.sa_handler = handle_signal;
// 		if(sigaction(SIGINT, &sa_int, NULL) == -1)
// 			printf("Sigaction failed\n");
// 		sigemptyset(&sa_int.sa_mask);
// 		char *input = readline("minishell> ");

// 		if (input)
// 		{
// 			int i;

// 			i = 0;
// 			dest = ft_split(input, ' ');
// 			tokens.str = malloc(sizeof(char *) * strlen(input));
// 			while(dest[i] != NULL)
// 			{
// 				detect_str(dest[i], tokens);
// 				i++;
// 			}
// 			add_history(input);
// 			if(ft_strncmp(input, "clear", 5) == 0)
// 				rl_clear_history();
// 			free(input);
// 		}
// 		else if(!input)
// 			break;
// 		else {
// 			printf("Error reading input.\n");
// 		}

// 	}
// 	return 0;
// }

