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
	{//printf("AAAAA::%s\n", line + i);
		while (indic == 0 && line[i])
		{//printf("BBBBB\n");
			while (line[i] != '\'' && line[i])
				i++;
			char *tempo1 = NULL;
			tempo1 = malloc(sizeof(char *));
			strncpy(tempo1, line + start, i - start);
			printf("|%i| && %s\n", i, tempo1);
			splited = ft_split(tempo1, ' ');
			while(splited[s_count] != NULL)
			{
				tokens[t_count] = splited[s_count];
				s_count++;
				t_count++;
			}
			if (!line[i])
				break ;
			else
			{
				s_count = 0;
				indic = 1;
				i++;
				temp = i;
			}
		}
		while (indic == 1 && line[i])
		{//printf("CCCCC::%s\n", line + i);
			while (line[i] != '\'' && line[i])
				i++;
			char *tempo = NULL;
			tempo = malloc(sizeof(char *));
			strncpy(tempo, line + temp, i - temp);
			tokens[t_count] = tempo;
			if (!line[i])
				break ; 
			else
			{
				indic = 0;
				i++;
				t_count++;
				start = i;
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
		tokens = tokeniser(line);
		i = 0;
		while(tokens[i])
		{
			printf("{%s} ", tokens[i]);
			i++;
		}
		printf("\n");
	}
	// printf("\n");
	return 0;
}