#include "minishell.h"

void	expanser(char *envp[], l_tokens **head)
{
	int i = 0;
	int j = 0;
	int mall_len = 0;
	int param_len = 0;
	char *new_tok;

	l_tokens *tmp;
	tmp = *head;

	while (tmp)
	{
		if (tmp->token[0] == '\"')
		{
			while (tmp->token[i])
			{
				if (tmp->token[i] == '$')
				{
					++i;
					while (tmp->token[i + param_len] != ' ' && tmp->token[i + param_len] != '\"')
					{
						++param_len;
					}
					while (envp[j])
					{
						if (strncmp(tmp->token + i, envp[j], param_len) == 0)
						{
							// printf("%s\n", envp[j]);
							mall_len += strlen(envp[j]) - param_len - 1;
						}
						j++;
					}
					i += param_len;
					j = 0;
					param_len = 0;
				}
				if (tmp->token[i] != '\"')
					++mall_len;
				++i;
			}
			// printf("%i\n", mall_len);
			new_tok = malloc(mall_len + 1);
			i = 0;
			j = 0;
			mall_len = 0;
			param_len = 0;


			while (tmp->token[i])
			{
				if (tmp->token[i] == '$')
				{
					++i;
					while (tmp->token[i + param_len] != ' ' && tmp->token[i + param_len] != '\"')
					{
						++param_len;
					}
					while (envp[j])
					{
						if (strncmp(tmp->token + i, envp[j], param_len) == 0)
						{
							strcpy(new_tok + mall_len, envp[j] + param_len + 1);
							// printf("%s\n", envp[j]);
							mall_len += strlen(envp[j]) - param_len - 1;
						}
						j++;
					}
					i += param_len;
					j = 0;
					param_len = 0;
				}
				if (tmp->token[i] != '\"')
				{
					new_tok[mall_len] = tmp->token[i];
					++mall_len;
				}
				++i;
			}
			char *tmp_chr;
			tmp_chr = tmp->token;
			tmp->token = new_tok;
			i = 0;
			j = 0;
			mall_len = 0;
			param_len = 0;
		}
		tmp = tmp->next;
	}

}