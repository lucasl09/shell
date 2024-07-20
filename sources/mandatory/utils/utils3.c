/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:12:33 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/13 15:12:35 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	for_treeleft(t_tree **lst, t_tree *new)
{
	t_tree	*last;

	last = NULL;
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->left != NULL)
		last = last->left;
	last->left = new;
	last->left_token = NULL;
}

void	for_treeright(t_tree **lst, t_tree *new)
{
	t_tree	*last;

	last = NULL;
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->right != NULL)
		last = last->right;
	last->right = new;
	last->right_token = NULL;
}

t_type_r	open_file(const char *content)
{
	int	fd;

	fd = open(content, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (FT_ERROR);
	}
	close(fd);
	return (TRUE);
}

t_type_tree	initialize_type(char *content, t_tokens token)
{
	t_type_tree	tree_type;

	if (token == WORD)
		tree_type = STRING;
	else if (token == CMD_TOKEN)
		tree_type = COMMAND;
	else if (token == FILE_TOKEN)
		tree_type = FILENAME;
	else if (token == DELIMITER_TOKEN)
		tree_type = DELIMITER;
	else
		tree_type = token + 11;
	return (tree_type);
}

void	tree_build_nodes(t_token *new_node, t_tree **tree_lists, int direction)
{
	t_tree	*new;

	new = tree_new(ft_strdup(new_node->content), new_node->token);
	if (direction == TO_LEFT)
		for_treeleft(tree_lists, new);
	else
		for_treeright(tree_lists, new);
	free (new_node->content);
	new_node->content = NULL;
	new_node->token = NONE;
	return ;
}