<<<<<<< HEAD

=======
>>>>>>> 48c5e6d8b54b87845a288926355f7910e7802500
#ifndef __DOUBLY_LINKED_LIST_H__
# define __DOUBLY_LINKED_LIST_H__

#include <stdlib.h>

typedef struct		s_node
{
	struct s_node		*prev;
	void						*value;
	struct s_node		*next;
}									t_node;

// Given a ref to the head of DLL && it append a new Node at the end.
t_bool	append(t_node **head, void *data);

// Given a ref to the head of DLL && it pushs a new Node at the beginning
t_bool	push(t_node **head, void *data);

// Reverse the Linked list before pushing it to the file
t_node		*reverse_ll(t_node *head);

#endif
