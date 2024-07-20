#include <readline/readline.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../../includes/mandatory/mini_shell.h"

static void	validate_content(char **has_arg, int i, t_tree *current)
{
	if ((current->content)[0] == '\'' || (current->content)[0] == '\"')
		has_arg[i] = in_quote_getarg(current->content);
	else
		has_arg[i] = get_cmds_args_word(current->content);
}

static char	**get_has_arg_left(char **has_arg, int size, t_tree *node)
{
	t_tree	*current;

	current = node;
	while (current->left)
	{
		if (current->tree_type == COMMAND)
			size++;
		else
			return (NULL);
		current = current->left;
	}
	has_arg = ft_calloc(sizeof(char *), (size + 1));
	current = node;
	size--;
	while (size >= 0)
	{
		validate_content(has_arg, size, current);
		current = current->left;
		size--;
	}
	return (has_arg);
}

static char	**get_has_arg_right(char **has_arg, int size, t_tree *node)
{
	t_tree	*current;
	int		i;

	current = node;
	i = 0;
	while (current->right)
	{
		if (current->tree_type == COMMAND)
			size++;
		else
			return (NULL);
		current = current->right;
	}
	has_arg = ft_calloc(sizeof(char *), (size + 1));
	current = node;
	size--;
	while (i <= size)
	{
		validate_content(has_arg, i, current);
		current = current->right;
		i++;
	}
	return (has_arg);
}

char	**get_has_arg(t_tree *node, int direction)
{
	char	**has_arg;
	int		size;

	size = 1;
	has_arg = NULL;
	if (direction == TO_LEFT)
		has_arg = get_has_arg_left(has_arg, size, node);
	else
		has_arg = get_has_arg_right(has_arg, size, node);
	return (has_arg);
}

char	**get_path(t_venv **envp, char *var, char *cmd)
{
	t_venv	*envp_tmp;
	char		**full_path;

	if (!*envp)
		return (NULL);
	envp_tmp = env_lstsearch(envp, var);
	if (!envp_tmp)
	{
		full_path = (char **)malloc(sizeof(char *) * (2));
		full_path[0] = ft_strdup(cmd);
		full_path[1] = NULL;
	}
	else
		full_path = ft_split(envp_tmp->value, ':');
	return (full_path);
}
