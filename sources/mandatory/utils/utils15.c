#include "../../../includes/mandatory/mini_shell.h"

t_token	*for_tredirect(int *i, char *cmd_line, char c)
{
	t_token	*token;

	if (cmd_line[(*i) + 1] == c)
	{
		if (c == '<')
			token = newtoken(ft_strndup(&cmd_line[(*i)++], 2), DLESS);
		else
			token = newtoken(ft_strndup(&cmd_line[(*i)++], 2), DGREAT);
	}
	else
	{
		if (c == '<')
			token = newtoken(ft_strndup(&cmd_line[*i], 1), LESS);
		else
			token = newtoken(ft_strndup(&cmd_line[*i], 1), GREAT);
	}
	return (token);
}

void	for_tquote(char *cmd_line, int *size)
{
	int	inside_quote;

	inside_quote = FALSE;
	while (cmd_line[*size])
	{
		if (ft_isspace(cmd_line[*size]) == 0)
		{
			if (cmd_line[*size] == '\'' || cmd_line[*size] == '\"')
				inside_quote = !inside_quote;
			(*size)++;
		}
		else if (inside_quote == TRUE && ft_isspace(cmd_line[*size]) == 1)
			(*size)++;
		else
			break ;
	}
}

t_token	*last_history_cmd(t_token *current)
{
	while (current->next)
	{
		if (current->next->token == CMD_TOKEN)
			current = current->next;
		else
			return (current);
	}
	return (current);
}

void	fix_ttokens(t_token *target, t_token *first_cmd, t_token *last_cmd,
				t_token *input)
{
	t_token	*operator;

	if (target->token == CMD_TOKEN)
	{
		operator = target->next;
		target->next = first_cmd;
		first_cmd->prev = target;
		last_cmd->next = operator;
		if (operator != NULL)
			operator->prev = last_cmd;
		input->prev = target;
	}
	else
	{
		operator = target;
		if (target->prev != NULL)
			target->prev->next = first_cmd;
		first_cmd->prev = target->prev;
		last_cmd->next = operator;
		input->prev = target->prev;
		if (operator != NULL)
			operator->prev = last_cmd;
	}
}

static char	*get_key(char *envp, int *len_key)
{
	char	*key;

	*len_key = 0;
	while (envp[*len_key] != '=')
		(*len_key)++;
	key = ft_strndup(envp, *len_key);
	*len_key += 1;
	return (key);
}

void	get_envp(t_venv **envp, char **environ)
{
	char	*key;
	char	*value;
	int		index;
	int		len_key;

	index = 0;
	len_key = 0;
	while (environ[index])
	{
		key = get_key(environ[index], &len_key);
		value = ft_strdup(environ[index] + len_key);
		env_lstadd_back(envp, env_lstnew(key, value));
		index++;
		free (key);
		free (value);
	}
}
