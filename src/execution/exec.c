#include "minishell.h"

void	closeallpipes(t_command *command)
{
	int	j;

	j = -1;
	while (++j <= command->pipe_count)
	{
		close(command->scmd[j].pipe[0]);
		close(command->scmd[j].pipe[1]);
		close(command->scmd[j].stdio[0]);
		close(command->scmd[j].stdio[1]);
	}
	close(command->origio[0]);
	close(command->origio[1]);
}

void	closefdfree(t_command *command, char ***paths)
{
	int	i;

	dup2(command->origio[0], STDIN_FILENO);
	dup2(command->origio[1], STDOUT_FILENO);
	closeallpipes(command);
	i = -1;
	while (*paths && (*paths)[++i])
		safe_free((void **)(&((*paths)[i])));
	safe_free((void **)paths);
}

void	exec(char *path, t_command *command, int i, t_envvar *env)
{
	char	**arr;

	command->scmd[i].pid = fork();
	if (!command->scmd[i].pid)
	{
		arr = ll_to_arr(env);
		closeallpipes(command);
		execve(path, command->scmd[i].tokarr, arr);
		exit(1);
	}
}

int	execbuiltins(t_simpcmd *scmd, t_command *command, t_env *en)
{
	int	ret;

	ret = 0;
	if (str_cmp(scmd->tokarr[0], "echo"))
		echo(scmd);
	if (str_cmp(scmd->tokarr[0], "cd"))
		ret = cd(scmd);
	if (str_cmp(scmd->tokarr[0], "pwd"))
		pwd();
	if (str_cmp(scmd->tokarr[0], "env"))
		env(en->envll);
	if (str_cmp(scmd->tokarr[0], "unset"))
		unset(en->envll, scmd, &en->exitcode);
	if (str_cmp(scmd->tokarr[0], "export"))
		exportt(en->envll, scmd, &en->exitcode);
	if (str_cmp(scmd->tokarr[0], "exit"))
		ret = my_exit(en, scmd, command->pipe_count, en->exitcode);
	if (ret)
		en->exitcode = ret;
	return (1);
}
