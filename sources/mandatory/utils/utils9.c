#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include "../../../includes/mandatory/mini_shell.h"

static void	validate_content(char **cmd_args, int i, t_tree *current)
{
	if ((current->content)[0] == '\'' || (current->content)[0] == '\"')
		cmd_args[i] = ft_with_quote(current->content);
	else
		cmd_args[i] = ft_with_word(current->content);
}

static char	**get_cmd_args_left(char **cmd_args, int size, t_tree *node)
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
	cmd_args = ft_calloc(sizeof(char *), (size + 1));
	current = node;
	size--;
	while (size >= 0)
	{
		validate_content(cmd_args, size, current);
		current = current->left;
		size--;
	}
	return (cmd_args);
}

static char	**get_cmd_args_right(char **cmd_args, int size, t_tree *node)
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
	cmd_args = ft_calloc(sizeof(char *), (size + 1));
	current = node;
	size--;
	while (i <= size)
	{
		validate_content(cmd_args, i, current);
		current = current->right;
		i++;
	}
	return (cmd_args);
}

char	**get_cmd_args(t_tree *node, int direction)
{
	char	**cmd_args;
	int		size;

	size = 1;
	cmd_args = NULL;
	if (direction == LEFT)
		cmd_args = get_cmd_args_left(cmd_args, size, node);
	else
		cmd_args = get_cmd_args_right(cmd_args, size, node);
	return (cmd_args);
}

char	**get_path(t_venv **envp, char *var, char *cmd)
{
	t_venv	*envp_temp;
	char		**full_path;

	if (!*envp)
		return (NULL);
	envp_temp = env_lstsearch(envp, var);
	if (!envp_temp)
	{
		full_path = (char **)malloc(sizeof(char *) * (2));
		full_path[0] = ft_strdup(cmd);
		full_path[1] = NULL;
	}
	else
		full_path = ft_split(envp_temp->value, ':');
	return (full_path);
}
