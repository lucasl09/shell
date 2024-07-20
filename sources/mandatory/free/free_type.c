/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:34:57 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/07/13 13:55:22 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

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
		free(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

void	free_list(t_tree **tree_lists, t_token **token_list)
{
	if (tree_lists)
	{
		treelst_clear(tree_lists);
		free (*tree_lists);
		*tree_lists = NULL;
	}
	if (token_list)
	{
		clear_tokens(token_list);
		free(*token_list);
		*token_list = NULL;
	}
}

void	free_data(t_data **data)
{
	if ((*data)->tree_lists)
		treelst_clear(&(*data)->tree_lists);
	if ((*data)->token_list)
		clear_tokens(&(*data)->token_list);
	(*data)->tree_lists = NULL;
	(*data)->envp = NULL;
	(*data)->token_list = NULL;
	if (*data)
		free(*data);
	*data = NULL;
}


void	fkclose(int *fd, char *error)
{
	if (error)
		perror(error);
	if (*fd)
	{
		close(fd[0]);
		if (fd[1])
			close(fd[1]);
	}
}

void	free_trash(char **trash)
{
	int	index;

	if (!trash)
		return ;
	index = 0;
	while (trash[index])
	{
		if (trash[index])
			free(trash[index]);
		index++;
	}
	free(trash);
}

void	free_envp(t_venv **envp)
{
	t_venv	*current;
	t_venv	*next;

	if (!*envp)
		return ;
	current = *envp;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*envp = NULL;
}

void	free_ptargs(char **path_args, char **args)
{
	if (path_args)
		free_trash(path_args);
	if (args)
		free_trash(args);
}