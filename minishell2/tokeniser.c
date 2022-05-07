#include "minishell.h"

void	tokeniser(char *line, l_tokens **head)
{
	l_tokens *tmp;
	tmp = *head;

	l_tokens *last;
	last = *head;

	int i = 0;
	int s_count = 0;
	int start1 = 0;
	int start2 = 0;
	int indic = 0;
	char **splited;

	//allocated
	
	char *tempo2 = NULL;

	while (line[i])
	{
		while (indic == 0 && line[i])
		{
			while (line[i] != '\'' && line[i] != '\"' && line[i])
				i++;
			char *tempo1 = NULL;
			tempo1 = strndup(line + start1, i - start1); //creating tempo1 and trimming the excess part from line, for spit. better to change split, by adding third argument for lenght
			splited = ft_split(tempo1, ' '); //need to be double freed
			free(tempo1);
			tempo1 = NULL; //???????
			while(splited[s_count] != NULL)
			{
				tmp = createnode(splited[s_count]);
				tmp->prev = last;
				if (*head == NULL)
				{
					*head = tmp;
					last = *head;
				}
				else
				{
					last->next = tmp;
					last = last->next;
				}
				// tmp->next = *head;
				// *head = tmp;
				s_count++;
			}
			if (!line[i])
			{
				break ;
			}
			else
			{
				s_count = 0;
				if (line[i] == '\'')
					indic = 1;
				else
					indic = 2;
				++i;
				start2 = i;
			}
		}
		while (indic == 1 && line[i])
		{
			while (line[i] != '\'' && line[i])
				++i;
			
			tempo2 = strndup(line + start2, i - start2);
			tmp = createnode(tempo2); // tempo2/content need to be freed at the end
			tmp->prev = last;
			if (*head == NULL)
			{
				*head = tmp;
				last = *head;
			}
			else
			{
				last->next = tmp;
				last = last->next;
			}
			if (!line[i])
				break ; 
			else
			{
				indic = 0;
				i++;
				start1 = i;
			}
		}
		while (indic == 2 && line[i])
		{
			while (line[i] != '\"' && line[i])
				i++;
			tempo2 = strndup(line + start2 - 1, i - start2 + 2);
			tmp = createnode(tempo2); // tempo2/content need to be freed at the end
			tmp->prev = last;
			if (*head == NULL)
			{
				*head = tmp;
				last = *head;
			}
			else
			{
				last->next = tmp;
				last = last->next;
			}
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