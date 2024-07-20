#include "../../../includes/mandatory/mini_shell.h"

static void	division_args_cmds(t_token **token_list, t_tree **tree_lists)
{
	t_token	*current_token;
	t_tree	*current_tree;

	current_token = last_token(*token_list);
	current_tree = *tree_lists;
	if (current_tree == NULL)
	{
		tree_build_nodes(current_token, tree_lists, TO_LEFT);
		current_token = current_token->prev;
		current_tree = *tree_lists;
	}
	while (current_token)
	{
		tree_build_nodes(current_token, &current_tree, TO_LEFT);
		current_token = current_token->prev;
		current_tree = current_tree->left;
	}
}

static void	start_tree(t_token **token_list, t_tokens operator, t_tree **tree_lists)
{
	t_token	*current;

	while (operator > 5)
	{
		current = last_token(*token_list);
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
	current = last_token(*token_list);
	if (current->prev == NULL)
	{
		tree_build_nodes(current, tree_lists, TO_LEFT);
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
			for_left_node(6, *tree_lists, tree_lists, FT_ERROR);
		else
		{
			while (operator > 5)
			{
				for_left_node(operator, *tree_lists, tree_lists, FT_ERROR);
				for_right_node(operator, *tree_lists, tree_lists, FT_ERROR);
				operator--;
			}
		}
	}
	else if (*tree_lists == NULL)
		division_args_cmds(token_list, tree_lists);
}
