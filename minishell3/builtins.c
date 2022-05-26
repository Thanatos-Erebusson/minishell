#include "minishell.h"

void	env(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		printf("%s\n", envp[i]);
		++i;
	}
}

void	echo(l_tokens *tmp)
{
	while (tmp->next)
	{
		tmp = tmp->next;
		printf("%s", tmp->token);
	}
	printf("\n");
}

int	builtins(l_tokens **head, char **envp)
{
	// int i = 0;
	l_tokens *tmp = *head;

	if (strcmp(tmp->token, "echo") == 0)
	{
		echo(tmp);
		return 1;
	}
	else if (strcmp(tmp->token, "env") == 0)
	{
		env(envp);
		return 1;
	}
	else if (strcmp(tmp->token, "exit") == 0)
	{
		free_list(head);
		exit(1);
	}
	return 0;
}