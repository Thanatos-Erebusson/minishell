#include "minishell.h"

void delnode(l_tokens **node, l_tokens **head)
{
	if ((*node)->next && (*node)->prev)
	{
		(*node)->next->prev = (*node)->prev;
		(*node)->prev->next = (*node)->next;
	}
	else if ((*node)->next && !(*node)->prev)
	{
		*head = NULL;
		(*node)->next->prev = NULL;
	}
	else if (!(*node)->next && !(*node)->prev)
	{
		*head = NULL;
	}
	else if (!(*node)->next && (*node)->prev)
	{
		(*node)->prev->next = NULL;
	}
	free((*node));
}

void	remove_quotes(l_tokens *token)
{
	int i = 0;
	char *old = NULL;

	old = token->token;
	if ((old[0] == '\'' || old[0] == '\"'))
	{
		while (old[i])
			i++;
		token->token = strndup(old + 1, i - 2);
		free(old);
	}
}

char	*find_env(char *str, char *envp[], int len)
{
	int i = 0;
	
	while (envp[i])
	{
		if (envp[i][len] == '=' && strncmp(str, envp[i], len) == 0)
		{
			return (strdup(envp[i] + len + 1));
		}
		++i;
	}
	return (NULL);
}

char	*connector(int i, l_tokens *tmp, char *new_tok, char *envp[])
{
	int param_len = 0;
	char *env;
	char *tmp_tok;
	char *old_tok = tmp->token;

	tmp->token[i] = '\0';
	++i;
	while (tmp->token[i + param_len] != ' ' && tmp->token[i + param_len] != '\0')
		++param_len;
	env = find_env(tmp->token + i, envp, param_len);
	tmp_tok = ft_strjoin(tmp->token, env);
	new_tok = ft_strjoin(tmp_tok, tmp->token + param_len + i);
	if (old_tok != NULL && old_tok != tmp_tok)
		free(old_tok);
	if (tmp_tok != NULL && tmp_tok != new_tok)
		free(tmp_tok);
	if (env != NULL && env != new_tok)
		free(env);
	return (new_tok);
}

void	because_norm(l_tokens *tmp, l_tokens **head, char *old_tok, char *new_tok, char *envp[])
{
	int i;
	int indicquote = 0;

	i = 0;
	if (tmp->token[0] == '\"')
		indicquote = 1;
	remove_quotes(tmp);
	old_tok = tmp->token;
	while (tmp->token[i])
	{
		if (tmp->token[i] == '$')
		{
			if (tmp->token[i + 1] == '\0')
			{
				if (tmp->next && tmp->next->token[0] == '\'')
					tmp->token[i] = '\0';
				break;
			}
			new_tok = connector(i, tmp, new_tok, envp);
			if (!new_tok && indicquote == 0)
			{
				delnode(&tmp, head);
				break ;
			}
			else if (!new_tok && indicquote == 1)
			{
				new_tok = strdup("\0");
			}
			old_tok = new_tok;
			tmp->token = new_tok;
			i = 0;
		}
		if (tmp->token[i])
			++i;
	}
}

void	expanser(char *envp[], l_tokens **head)
{
	char *new_tok = NULL;
	char *old_tok = NULL;

	l_tokens *tmp;
	tmp = *head;
	while (tmp)
	{
		if (tmp->token[0] != '\'')
		{
			because_norm(tmp, head, old_tok, new_tok, envp);
		}
		else
			remove_quotes(tmp);
		tmp = tmp->next;
	}
}