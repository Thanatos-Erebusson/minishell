#include "minishell.h"

// int	linehandler(char *line)
// {
// 	int i = 0;
// 	int indic = 0;
// 	if (!(strlen(line) > 0))
// 		return 0;
// 	while (line[i])
// 	{
// 		++i;
// 		if (line[i] && line[i] != ' ')
// 		{
// 			++indic;
// 		}
// 	}
// 	if (indic == 0)
// 		return 0;
// 	return 1;
// }

char	*findPath(char *envp[], l_tokens *head)
{
	int i = 0;
	char *token;
	char *joined;
	char **paths;
	
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH", 4) == 0)
			break;
		i++;
	}
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	token = ft_strjoin("/", head->token);
	while (paths[i])
	{
		joined = ft_strjoin(paths[i], token);
		if (access(head->token, F_OK) == 0)            // if command has absolute path
		{
			free(joined);
			freedouble(paths);
			return(head->token);
		}
		if (access(joined, F_OK) == 0)                 // if command has relative path
		{
			free(token);
			freedouble(paths);
			return(joined);
		}
		free(joined);
		i++;
	}
	free(token);
	freedouble(paths);
	return(NULL);
}

void	execute(char *arg, char *envp[], l_tokens *head)
{
	// int i = 0;
	char **arr = listToarr(head);
	arr[0] = arg;
	// while (arr[i])
	// {
	// 	printf("%s\n", arr[i]);
	// 	i++;
	// }
	// char *arr[] = {
	// 	arg,
	// 	"bomb",
	// 	NULL
	// };
	
	int id = fork();
	if (id == 0)
	{
		execve(arg, arr, envp);
	}
	else
	{
		wait(NULL);
	}
	free(arr);
	if (head->token != arg)         // if command has absolute path
		free(arg);
}

void	free_list(l_tokens **head)
{
	if (!head)
		return ;
	while((*head)->next)					// < Freeing lists
	{
		free((*head)->token);
		(*head) = (*head)->next;
		free((*head)->prev);
	}
	free((*head)->token);
	free((*head));							// >
	*head = NULL;
}

int main(int argc, char *argv[], char *envp[])
{
	char *line;
	l_tokens *head = NULL;
	// int	i = 0;
	char *arg = NULL;
	printf("\033[0;32m");
	while(1)
    {
		head = NULL;
		
		line = readline("myshell: ");
		add_history(line);				//init history

		tokeniser(line, &head);

		free(line);
		// l_tokens *tmp;
		// 	tmp = head;
		// 	while (tmp)
		// 	{
		// 		printf("{%s}\n", tmp->token);
		// 		tmp = tmp->next;
		// 	}
		
		if (head)
		{
			expanser(envp, &head);

			if (!builtins(&head, envp))
			{
				arg = findPath(envp, head);
				if (envp)
					execute(arg, envp, head);
			}

			l_tokens *tmp;
			tmp = head;
			while (tmp)
			{
				printf("{%s}\n", tmp->token);
				tmp = tmp->next;
			}
			// printf("\033[1;31m");
			// printf("AAAA\n");
			free_list(&head);
		}


		// while(head)
		// {
		// 	printf("{%s} ", head->token);
		// 	head = head->prev;
		// }
		// printf("\n");
	}
	return 0;
}