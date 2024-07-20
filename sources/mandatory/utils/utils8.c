#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

static void	rebuild_quote(char *content, char **full_line, char *remove_quotes,
		int i)
{
	char	*tmp;
	char	*old_line;
	int		start;

	start = ++i;
	while (content[i])
	{
		if (ft_isspace(content[i]) == 0 && content[i] != '\''
			&& content[i] != '\"')
			i++;
		else
			break ;
	}
	tmp = ft_strndup(&(content[start]), i - start);
	*full_line = ft_strjoin(remove_quotes, tmp);
	free(tmp);
	free(remove_quotes);
	if (content[i] == '\'' || content[i] == '\"')
	{
		old_line = *full_line;
		tmp = in_quote_getarg(&(content[i]));
		*full_line = ft_strjoin(*full_line, tmp);
		free(tmp);
		free(old_line);
	}
}

char	*in_quote_getarg(char *content)
{
	char	*remove_quotes;
	int		i;
	char	*full_line;
	char	quote;

	if (ft_strncmp(content, "\"\"", 2) == 0)
		return (NULL);
	remove_quotes = NULL;
	quote = '\0';
	i = 0;
	quote = content[i++];
	while (content[i])
	{
		if (content[i] != quote)
			i++;
		else
			break ;
	}
	remove_quotes = ft_strndup(&(content[1]), i - 1);
	if (content[i + 1] == '\0')
		return (remove_quotes);
	rebuild_quote(content, &full_line, remove_quotes, i);
	return (full_line);
}

static char	*get_type_cmdarg(char *content)
{
	int		i;
	char	*line;

	i = 0;
	while (content[i])
	{
		if (content[i] != '\'' && content[i] != '\"')
			i++;
		else
			break ;
	}
	line = ft_strndup(&(content[0]), i);
	return (line);
}

static void	rebuild_word(char **full_line, char *tmp, int *i, int has_quote)
{
	char	*line;

	if (*full_line == NULL)
		*full_line = ft_strdup(tmp);
	else if (tmp != NULL)
	{
		line = *full_line;
		*full_line = ft_strjoin(line, tmp);
		free(line);
	}
	if (tmp == NULL)
		*i += 2;
	else
	{
		*i += (ft_strlen(tmp) + has_quote);
		free(tmp);
	}
}

char	*get_cmds_args_word(char *content)
{
	int		i;
	char	*full_line;
	char	*tmp;
	int		has_quote;

	i = 0;
	full_line = NULL;
	while (content[i])
	{
		has_quote = 0;
		if (content[i] == '\'' || content[i] == '\"')
		{
			tmp = in_quote_getarg(&(content[i]));
			has_quote = 2;
		}
		else
			tmp = get_type_cmdarg(&(content[i]));
		rebuild_word(&full_line, tmp, &i, has_quote);
	}
	return (full_line);
}