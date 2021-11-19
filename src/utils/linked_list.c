#include "minishell.h"

t_node	*new_node(void *data)
{
	t_node	*node;

	if (!data)
		return (NULL);
	node = malloc(sizeof(*(node)));
	if (!node)
		return (NULL);
	node->prev = NULL;
	node->data = data;
	node->next = NULL;
	return (node);
}

/**
**  
**  @param list list where to add data
**  @param data data pointer to add to the list
**  @return pointer to the added/last node
** 
*/
t_node	*push_back(t_node **list, void *data)
{
	t_node	*node;

	if (!data)
		return (NULL);
	if (!*list)
	{
		*list = new_node(data);
		return (*list);
	}
	node = *list;
	while (node->next)
		node = node->next;
	node->next = new_node(data);
	node->next->prev = node;
	return (node->next);
}

void	push_front(t_node **list, void	*data)
{
	t_node	*node;

	node = new_node(data);
	if (!*list)
		*list = node;
	else if (node)
	{
		((t_node *)*list)->prev = node;
		node->next = *list;
		*list = node;
	}
}

size_t	list_size(t_node	*list)
{
	t_node	*tmp;
	size_t	i;

	if (list == NULL)
		return (0);
	tmp = list;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/**
**  Get the nth node from a linked list
**
**  @param list to get the nth node from
**  @param n number of the node to get,
**		   if n == -1 it gets the last node
**  @return the nth node
**/
t_node	*get_n_node(t_node *list, int n)
{
	t_node	*node;
	int		i;

	node = list;
	if (node == NULL)
		return (NULL);
	if (n == -1)
	{
		while (node->next)
			node = node->next;
		return (node);
	}
	i = 0;
	while (i++ < n && node)
		node = node->next;
	return (node);
}
