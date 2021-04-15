
#include "minishell.h"

t_bool	push(t_node **head, void *data)
{
	t_node		*new_node;

	if (!(new_node = malloc(sizeof(t_node))))
		return (1);
	new_node->value = data;
	new_node->next = (*head);
  new_node->prev = NULL;
	return (0);
}

t_bool	append(t_node **head, void *data)
{
	t_node		*new_node;
	t_node		*last;

	if (!(new_node = malloc(sizeof(t_node))))
		return (1);
	new_node->value = data;
	new_node->next = NULL;

	if (*head == NULL)
	{
		new_node->prev = NULL;
		*head = new_node;
		return 0;
	}

	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;

  return 0;
}

void	reverse(t_node **head)
{
	t_node *temp;
	t_node *current;

	temp = NULL;
	current = *head;

	while (current !=  NULL)
	{
	  temp = current->prev;
	  current->prev = current->next;
	  current->next = temp;
	  current = current->prev;
	}

	if(temp != NULL)
		*head= temp->prev;
}
