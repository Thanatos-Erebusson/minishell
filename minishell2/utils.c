#include "minishell.h"

void	freedouble(char **alloc)
{
	int i = 0;

	while (alloc[i])
	{
		free(alloc[i]);
		i++;
	}
	free(alloc);
}

int	listlen(l_tokens *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

l_tokens	*createnode(char *content)
{
	l_tokens *new;
	new = malloc(sizeof(*new));
	new->token = content;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

char	**listToarr(l_tokens *head)
{
	int i = 0;
	int len = listlen(head);
	char **arr = malloc(sizeof(char *) * len + 1);

	while (head)
	{
		arr[i] = head->token;
		i++;
		head = head->next;
	}
	arr[i] = NULL;
	return arr;
}