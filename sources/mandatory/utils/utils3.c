#include "../../../includes/mandatory/mini_shell.h"

void	tree_add_left(t_tree **lst, t_tree *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	t_tree *last = *lst;
	while (last->left != NULL)
		last = last->left;
	last->left = new;
}

void	tree_add_right(t_tree **lst, t_tree *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	t_tree *last = *lst;
	while (last->right != NULL)
		last = last->right;
	last->right = new;
}

t_type_r	open_file(const char *content)
{
	int	fd;

	fd = open(content, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

type_tree	initialize_type(char *content, tokens token)
{
	type_tree	for_types;

	if (token == WORD)
	{
		if (content[0] == '"' || content[0] == '\'')
			for_types = STRING;
		else if (open_file(content))
			for_types = FILENAME;
		else
			for_types = COMMAND;
	}
	else
		for_types = token - 10;
	return (for_types);
}
