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

static void	division_args_cmds(t_token **token_list, t_tree **tree_lists)
{
	t_token	*current_token;
	t_tree	*current_tree;

	current_token = verify_lastlst(*token_list);
	current_tree = *tree_lists;
	if (current_tree == NULL)
	{
		initialize_treenode(current_token, tree_lists, LEFT);
		current_token = current_token->prev;
		current_tree = *tree_lists;
	}
	while (current_token)
	{
		initialize_treenode(current_token, &current_tree, LEFT);
		current_token = current_token->prev;
		current_tree = current_tree->left;
	}
}

static void	start_tree(t_token **token_list, t_tokens operator, t_tree **tree_lists)
{
	t_token	*current;

	while (operator > 5)
	{
		current = verify_lastlst(*token_list);
		while (current != NULL)
		{
			if (current->token == operator
				|| (operator == 6 && current->token > 2))
			{
				break_nodes(current, tree_lists, 0);
				return ;
			}
			else
				current = current->prev;
		}
		operator--;
	}
	return ;
}

static t_token	*validate_token_list(t_token **token_list, t_tree **tree_lists)
{
	t_token	*current;

	if (!*token_list || !(*token_list)->content)
		return (NULL);
	current = verify_lastlst(*token_list);
	if (current->prev == NULL)
	{
		initialize_treenode(current, tree_lists, LEFT);
		return (NULL);
	}
	return (current);
}

void	eotokens(t_token **token_list, t_tree **tree_lists)
{
	t_token		*current;
	int			operator;

	operator = PIPE;
	current = validate_token_list(token_list, tree_lists);
	if (current == NULL)
		return ;
	start_tree(token_list, operator, tree_lists);
	if (*tree_lists != NULL)
	{
		if ((*tree_lists)->tree_type != PIPE_LINE)
			for_left_cnodes(6, *tree_lists, tree_lists, FALSE);
		else
		{
			while (operator > 5)
			{
				for_left_cnodes(operator, *tree_lists, tree_lists, FALSE);
				for_right_cnodes(operator, *tree_lists, tree_lists, FALSE);
				operator--;
			}
		}
	}
	else if (*tree_lists == NULL)
		division_args_cmds(token_list, tree_lists);
}
