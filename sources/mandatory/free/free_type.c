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

void	free_evg(char **matrix)
{
	int	index;

	if (!matrix)
		return ;
	index = 0;
	while (matrix[index])
	{
		if (matrix[index])
			free(matrix[index]);
		index++;
	}
	free(matrix);
}

void	free_storage(t_data **data)
{
	if ((*data)->tree_lists)
		tree_clear(&(*data)->tree_lists);
	if ((*data)->token_list)
		clear_tokens(&(*data)->token_list);
	(*data)->tree_lists = NULL;
	(*data)->envp = NULL;
	(*data)->token_list = NULL;
	if (*data)
		free(*data);
	*data = NULL;
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

void	free_onlyargs(char **path_args, char **args)
{
	if (path_args)
		free_evg(path_args);
	if (args)
		free_evg(args);
}
