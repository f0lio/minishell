
#include "minishell.h"

t_node  *new_node(void *data)
{
	t_node *node;

	if (!data)
		return NULL;
	MALLOC(node);
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
		return NULL;
	if (!*list)
	{
		*list = new_node(data);
		return *list;
	}
	node = *list;
	while (node->next)
		node = node->next;
	node->next = new_node(data);
	node->next->prev = node;
	return node->next;
}

void	  push_front(LIST, void  *data)
{
	t_node	  *node;
	t_node	  *curr;

	node = new_node(data);
	if (!*list)
		*list = node;
	else if (node)
	{
		((t_node*)*list)->prev = node;
		node->next = *list;
		*list = node;
	}
}

void	list_iter(LIST, void(*fun)(void *))
{
	t_node	  *tmp;

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

void	clear_list(LIST)
{
	void	*(fun);
	fun = safe_free;
	list_iter(list, fun);
}

size_t  list_size(t_node	*list)
{
	t_node  *tmp;
	size_t  i;
		
	if (list == NULL)
		return (0);
	tmp = list;
	i = 0;
	while (tmp)
	{
		print("LIST_SIZE");
		print((char*)tmp->data);
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	destroy_list(LIST)
{
	t_node	  *p1;
	t_node	  *p2;

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

void	delete_list(LIST) 
{ 
   t_node *current;
   t_node *next;

   current = *list; 
   while (current != NULL)  
   { 
	   next = current->next; 
	   safe_free((void **)&current);
	   current = next; 
   } 
   *list = NULL; 
}

/**
**  Get the nth node from a linked list
**
**  @param list to get the nth node from
**  @param n number of the node to get,
**		   if n == -1 it gets the last node
**  @return the nth node
**/
t_node *get_n_node(t_node *list, int n)
{
	t_node  *node;
	int	 i;

	node = list;
	if (node == NULL)
		return NULL;
	if (n == -1)
	{
		while (node->next)
			node = node->next;
		return node;
	}
	i = 0;
	while (i++ < n && node)
		node = node->next;
	return node;
}
