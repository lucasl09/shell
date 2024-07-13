/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:34:57 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/06/29 16:00:13 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	free_list(t_tree **tree_list, t_token **token_list)
{
	if (tree_list)
	{
		treelst_clear(tree_list);
		free (*tree_list);
		*tree_list = NULL;
	}
	if (token_list)
	{
		clear_tokens(token_list);
		free(*token_list);
		*token_list = NULL;
	}
}

void	ft_free_tokens(t_token *tokens)
{
    t_token *current;
    t_token *next;

	current = tokens;
    while (current != NULL) {
		next = current->next;
		free(current->content);
        free(current);
		current = next;
	}
}

void	treelst_clear(t_tree **lst)
{
	t_tree	*current;
	t_tree	*right;

	if (*lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		right = current->right;
		if (current->left != NULL)
			treelst_clear(&(current->left));
		free(current->content);
		free(current);
		current = right;
	}
	*lst = NULL;
}

void	clear_tokens(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	if (*lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free (current->content);
		free (current);
		current = next;
	}
	*lst = NULL;
}
