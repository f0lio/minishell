#include "minishell.h"

void	destroy_list(t_node **list)
{
	t_node	*p1;
	t_node	*p2;

	if (*list == NULL)
		return ;
	p1 = *list;
	while (p1)
	{
		p2 = p1->next;
		safe_free((void **)&p1);
		p1 = p2;
	}
}

void	delete_list(t_node	**list)
{
	t_node	*current;
	t_node	*next;
	t_token	*t;

	current = *list;
	while (current)
	{
		t = (t_token *)current->data;
		next = current->next;
		safe_free((void **)&current);
		current = next;
	}
	*list = NULL;
}

void	list_iter(t_node **list, void (*fun)(void *))
{
	t_node	*tmp;

	if (list == NULL)
		return ;
	tmp = *list;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp != NULL)
	{
		(fun)(tmp->data);
		tmp = tmp->next;
	}
}

void	clear_list(t_node **list)
{
	void *(fun);
	fun = safe_free;
	list_iter(list, fun);
}
