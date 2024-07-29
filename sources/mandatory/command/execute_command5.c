#include "../../../includes/mandatory/mini_shell.h"
#include <stdio.h>

static void	cut_cmdargs(t_token **token_list, t_tree **tree_listed)
{
	t_token	*current_token;
	t_tree	*current_ast;

	current_token = token_lstlast(*token_list);
	current_ast = *tree_listed;
	if (current_ast == NULL)
	{
		build_tnode(current_token, tree_listed, LEFT);
		current_token = current_token->prev;
		current_ast = *tree_listed;
	}
	while (current_token)
	{
		build_tnode(current_token, &current_ast, LEFT);
		current_token = current_token->prev;
		current_ast = current_ast->left;
	}
}

static void	f_init_tree(t_token **token_list, t_tokens opr, t_tree **tree_listed)
{
	t_token	*current;

	while (opr > 5)
	{
		current = token_lstlast(*token_list);
		while (current != NULL)
		{
			if (current->token == opr
				|| (opr == 6 && current->token > 2))
			{
				cut_all(current, tree_listed, 0);
				return ;
			}
			else
				current = current->prev;
		}
		opr--;
	}
	return ;
}

static t_token	*valid_tlists(t_token **token_list, t_tree **tree_listed)
{
	t_token	*current;

	if (!*token_list || !(*token_list)->content)
		return (NULL);
	current = token_lstlast(*token_list);
	if (current->prev == NULL)
	{
		build_tnode(current, tree_listed, LEFT);
		return (NULL);
	}
	return (current);
}

void	eotokens(t_token **token_list, t_tree **tree_listed)
{
	t_token		*current;
	int			opr;

	opr = PIPE;
	current = valid_tlists(token_list, tree_listed);
	if (current == NULL)
		return ;
	f_init_tree(token_list, opr, tree_listed);
	if (*tree_listed != NULL)
	{
		if ((*tree_listed)->tree_type != PIPE_LINE)
			cut_tleft(6, *tree_listed, tree_listed, FALSE);
		else
		{
			while (opr > 5)
			{
				cut_tleft(opr, *tree_listed, tree_listed, FALSE);
				cut_tright(opr, *tree_listed, tree_listed, FALSE);
				opr--;
			}
		}
	}
	else if (*tree_listed == NULL)
		cut_cmdargs(token_list, tree_listed);
}
