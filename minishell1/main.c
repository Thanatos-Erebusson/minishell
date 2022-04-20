#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_tokens{
	char *token;
	struct s_tokens *next;
}l_tokens;

l_tokens	*addnode(char *content)
{
	l_tokens *new;
	new = malloc(sizeof(*new));
	new->token = content;
	new->next = NULL;
	return new;
}

void	tokeniser(char *line, l_tokens **head)
{
	l_tokens *tmp;
	tmp = *head;

	int i = 0;
	int s_count = 0;
	int start1 = 0;
	int start2 = 0;
	int indic = 0;
	char **splited;

	//allocated
	char *tempo1 = NULL;
	char *tempo2 = NULL;
	while (line[i])
	{printf("AAA\n");
		while (indic == 0 && line[i])
		{printf("BBB\n");
			while (line[i] != '\'' && line[i])
				i++;
			tempo1 = strndup(line + start1, i - start1); //creating tempo1 and trimming the excess part from line, for spit. better to change split, by adding third argument for lenght
			splited = ft_split(tempo1, ' '); //need to be freed
			free(tempo1);
			tempo1 = NULL; // ?????????
			while(splited[s_count] != NULL)
			{printf("CCC\n");
				tmp = addnode(splited[s_count]);
				tmp->next = *head;
				*head = tmp;
				s_count++;
			}
			if (!line[i])
				break ;
			else
			{
				s_count = 0;
				indic = 1;
				i++;
				start2 = i;
			}
		}
		while (indic == 1 && line[i])
		{
			while (line[i] != '\'' && line[i])
				i++;
			tempo2 = strndup(line + start2, i - start2); //need to be freed
			tmp = addnode(tempo2);
			tmp->next = *head;
			*head = tmp;
			if (!line[i])
				break ; 
			else
			{
				indic = 0;
				i++;
				start1 = i;
			}
		}
	}
}

int main(int argc, char *argv[], char *envp[])
{
	char *line;
	int i;

	l_tokens *head = NULL;

	while(1)
    {
		line = readline("myshell: ");
		tokeniser(line, &head);
		i = 0;
		while(head)
		{
			printf("{%s} ", head->token);
			head = head->next;
		}
		printf("\n");
	}
	return 0;
}