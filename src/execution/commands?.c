
// void	echo(t_command *command)
// {
// 	int	i;
	
// 	i = 1;
// 	if (command->tokens_count != 1 && str_cmp(command->tokens[i]->tok, "-n"))
// 		i++;
// 	while (i < command->tokens_count)
// 	{
// 		printf("%d\n", command->tokens[i]->quoted);
// 		printf("%s", command->tokens[i]->tok);
// 		i++;
// 		if (i < command->tokens_count)
// 			printf(" ");
// 	}
// 	if (!str_cmp(command->tokens[1]->tok, "-n"))
// 		printf("\n");
// }

// void	pwd(t_command *command)
// {
// 	i = 0;
// 	tokens = malloc(sizeof(char *) * command->tokens_count);
// 	while (i < command->tokens_count)
// 	{
// 		tokens[i] = command->tokens[i]->tok;
// 		i++;
// 	}
// 	pid = fork();
// 	if (!pid)
// 		execve("/bin/pwd", tokens, NULL);
// }