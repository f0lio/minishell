
# include "dbg_utils.h"

void exitfunc(int sig)
{
    _exit(0);
}

void    ft_exitTime(int argc, char **argv)
{
    int exitTime;

    exitTime = 20;
    if (argv[1][0] == 't' && argv[1][1] == '=')
        exitTime = atoi(&argv[1][2]);
    signal(SIGALRM, exitfunc);
    alarm(exitTime);
}

bool    nothing() {return 0;} //Yeah, I know..

void    debugMem(void *mem)
{
    ;
}

void debug_commands(ENV)
{
	put_str(GREEN);
	printf("-- COUNT -- : %d\n", env->cmds_count);
	for (int i = 0; i < env->cmds_count; i++)
	{
		put_str(RED);
		printf("-- Command: %d\n", i);
		put_str(NO_COLOR);
		print_tokens(&(env->commands[i]).tokens, (env->commands[i]).tokens_count);
	}
}