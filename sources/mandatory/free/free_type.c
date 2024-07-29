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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

void	free_args(char **path_args, char **args)
{
	if (path_args)
		free_trash(path_args);
	if (args)
		free_trash(args);
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

void	free_data(t_data **data)
{
	if ((*data)->tree_listed)
		treelst_clear(&(*data)->tree_listed);
	if ((*data)->token_list)
		tokenlst_clear(&(*data)->token_list);
	(*data)->tree_listed = NULL;
	(*data)->envp = NULL;
	(*data)->token_list = NULL;
	if (*data)
		free(*data);
	*data = NULL;
}
