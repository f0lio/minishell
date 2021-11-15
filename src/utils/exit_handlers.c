
#include "minishell.h"

void    exit_program(ENV, int exit_code)
{
    //free memory
    exit(exit_code);
}


void    destroy_env_vars(t_envvar **vars)
{
    t_envvar      *p1;
    t_envvar      *p2;

    if (*vars == NULL)
        return ;
	p1 = *vars;
    while (p1->prev)
    	p1 = p1->prev;
    while (p1)
    {
		p2 = p1->next;
		safe_free((void **)&p1->content);
		safe_free((void **)&p1->name);
		safe_free((void **)&p1);
		p1 = p2;
    }
}

void    destroy_env(ENV)
{
	reset_data(env);
	destroy_env_vars(&env->envll);
}
