#include "../../../includes/mandatory/mini_shell.h"

static t_token	*wordtoken(int *i, char *cmd_line)
{
	t_token	*token;
	int		size;
	int		has_quote;

	size = *i;
	has_quote = FT_ERROR;
	while (cmd_line[size])
	{
		if (cmd_line[size] == '\'' || cmd_line[size] == '\"')
		{
			size++;
			if (has_quote == FT_ERROR)
				has_quote = !has_quote;
			else
				break ;
		}
		else if (initialize_parsetoken(cmd_line, &size, has_quote) == -1)
			break ;
		if (cmd_line[size] == '|' && ft_isspace(cmd_line[--size]) == 0)
			break ;
	}
	token = newtoken(ft_strndup(&cmd_line[*i], size - *i), WORD);
	*i = size;
	return (token);
}

static t_token	*expansiontoken(int *i, char *cmd_line)
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

static t_token	*quotetoken(int *i, char *cmd_line)
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
		create_quote_token(cmd_line, &size);
	token = newtoken(ft_strndup(&cmd_line[*i], size - *i), WORD);
	*i = size - 1;
	return (token);
}

static int	build_token_type(t_token **token, int *i, char *cmd)
{
	if (cmd[*i] == '<' || cmd[*i] == '>')
		*token = redirecttoken(i, cmd);
	else if (cmd[*i] == '\'' || cmd[*i] == '\"')
		*token = quotetoken(i, cmd);
	else if (cmd[*i] == '|')
		*token = newtoken(ft_strndup(&cmd[*i], 1), PIPE);
	else if (cmd[*i] == '$')
		*token = expansiontoken(&(*i), cmd);
	else if (ft_isspace(cmd[*i]) == 0)
		*token = wordtoken(&(*i), cmd);
	else if (cmd[*i] == '\'' || cmd[*i] == '\"')
		*token = quotetoken(&(*i), cmd);
	if (*token == NULL)
		return (ERROR);
	else
		return (SUCESS);
}

int	build_token(char *cmd, t_token **token_list)
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
			build_token_type(&token, &i, cmd);
			if (token == NULL)
				return (ERROR);
		}
		if (token != NULL)
			token_to_back(token_list, token);
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