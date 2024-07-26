#include "../../../includes/mandatory/mini_shell.h"

static t_token	*build_word_token(int *i, char *cmd_line)
{
	t_token	*token;
	int		size;
	int		has_quote;

	size = *i;
	has_quote = FALSE;
	while (cmd_line[size])
	{
		if (cmd_line[size] == '\'' || cmd_line[size] == '\"')
		{
			size++;
			if (has_quote == FALSE)
				has_quote = !has_quote;
			else
				break ;
		}
		else if (parse_ttokens(cmd_line, &size, has_quote) == -1)
			break ;
		if (cmd_line[size] == '|' && ft_isspace(cmd_line[--size]) == 0)
			break ;
	}
	token = newtoken(ft_strndup(&cmd_line[*i], size - *i), WORD);
	*i = size;
	return (token);
}

static t_token	*build_expansion_token(int *i, char *cmd_line)
{
	t_token	*token;
	int		size;

	size = *i;
	size++;
	if (ft_isdigit(cmd_line[size]) != 0 || cmd_line[size] == '?')
		size++;
	if (cmd_line[size])
	{
		while (ft_isalpha(cmd_line[size]) != 0 || cmd_line[size] == '_')
			size++;
	}
	token = newtoken(ft_strndup(&cmd_line[*i], size - *i), EXPANSION);
	*i = size - 1;
	return (token);
}

static t_token	*build_quote_token(int *i, char *cmd_line)
{
	t_token	*token;
	int		size;
	char	quote;

	size = *i;
	quote = cmd_line[size];
	size++;
	while (cmd_line[size] && cmd_line[size] != quote)
		size++;
	if (!cmd_line[size])
		return (NULL);
	else
		size++;
	if (cmd_line[size] != '<' && cmd_line[size] != '>')
		for_tquote(cmd_line, &size);
	token = newtoken(ft_strndup(&cmd_line[*i], size - *i), WORD);
	*i = size - 1;
	return (token);
}

static int	create_token_type(t_token **token, int *i, char *cmd)
{
	if (cmd[*i] == '<' || cmd[*i] == '>')
		*token = initialize_rdt(i, cmd);
	else if (cmd[*i] == '\'' || cmd[*i] == '\"')
		*token = build_quote_token(i, cmd);
	else if (cmd[*i] == '|')
		*token = newtoken(ft_strndup(&cmd[*i], 1), PIPE);
	else if (cmd[*i] == '$')
		*token = build_expansion_token(&(*i), cmd);
	else if (ft_isspace(cmd[*i]) == 0)
		*token = build_word_token(&(*i), cmd);
	else if (cmd[*i] == '\'' || cmd[*i] == '\"')
		*token = build_quote_token(&(*i), cmd);
	if (*token == NULL)
		return (ERROR);
	else
		return (OK);
}

int	create_token(char *cmd, t_token **token_list)
{
	t_token	*token;
	int		i;

	i = 0;
	while (cmd[i])
	{
		token = NULL;
		if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|' || cmd[i] == '$'
			|| ft_isspace(cmd[i]) == 0 || cmd[i] == '\'' || cmd[i] == '\"')
		{
			create_token_type(&token, &i, cmd);
			if (token == NULL)
				return (ERROR);
		}
		if (token != NULL)
			put_lasttoken(token_list, token);
		if (cmd[i])
			i++;
	}
	if (cmd)
	{
		free(cmd);
		cmd = NULL;
	}
	return (TRUE);
}
