#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_tokens{
	char *token;
	struct s_tokens *next;
	struct s_tokens *prev;
}l_tokens;


void		tokeniser(char *line, l_tokens **head);
void		freedouble(char **alloc);
int			listlen(l_tokens *lst);
l_tokens	*createnode(char *content);
char		**listToarr(l_tokens *head);
void		expanser(char *envp[], l_tokens **head);
void		free_list(l_tokens **head);
int			builtins(l_tokens **head, char **envp);


#endif