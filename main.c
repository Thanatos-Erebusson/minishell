#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

char **tokeniser(char *line)
{
	int i = 0;
	int t_count = 0;
	int s_count = 0;
	int temp = 0;
	int start = 0;
	int indic = 0;
	char **tokens;
	char **splited;

	tokens = malloc(sizeof(char *) * 10);
	tokens[9] = NULL;
	while (line[i])
	{
		while (indic == 0)
		{
			if (line[i] != '\'')
				i++;
			else
			{
				splited = ft_split(line + start, ' ');
				while(splited[s_count] != NULL)
				{
					tokens[t_count] = splited[s_count];
					s_count++;
					t_count++;
				}
				s_count = 0;
				indic = 1;
				i++;
				temp = i;
			}
		}
		while (indic == 1)
		{
			if (line[i] != '\'')
				i++;
			else
			{
				strncpy(tokens[t_count], line + temp, i - temp);
				indic = 0;
				start = i;
				i++;
				t_count++;
			}
		}
	}
	return tokens;
}

int main(int argc, char *argv[], char *envp[])
{
	char *line;
	char **tokens;
	int i;

	while(1)
    {
		line = readline("myshell: ");
		printf("%s\n", line);
		tokens = tokeniser(line);
		i = 0;
		while(tokens[i])
		{
			printf("%s", tokens[i]);
			i++;
		}
		printf("\n");
	}
	// printf("\n");
	return 0;
}