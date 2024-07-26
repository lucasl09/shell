/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:04:52 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/13 16:19:07 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	input_rdt(t_tree *operator)
{
	t_tree	*tmp;
	int		file_fd;

	tmp = operator->right;
	file_fd = open(tmp->content, O_RDONLY);
	if (file_fd == -1)
	{
		fkclose(&file_fd, "minishell");
		return (KO);
	}
	if (dup2(file_fd, STDIN_FILENO) == -1)
	{
		fkclose(&file_fd, "minishell");
		return (KO);
	}
	close(file_fd);
	tmp = NULL;
	return (OK);
}

int	output_rdt(t_tree *operator)
{
	t_tree	*tmp;
	int		file_fd;

	tmp = operator->right;
	file_fd = open(tmp->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file_fd == -1)
	{
		fkclose(&file_fd, "minishell");
		return (KO);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		fkclose(&file_fd, "minishell");
		return (KO);
	}
	close(file_fd);
	tmp = NULL;
	return (OK);
}

int	rdt_expand(t_tree *operator)
{
	t_tree	*tmp;
	int		file_fd;

	tmp = operator->right;
	file_fd = open(tmp->content, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file_fd == -1)
	{
		fkclose(&file_fd, "minishell");
		return (KO);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		fkclose(&file_fd, "minishell");
		return (KO);
	}
	close(file_fd);
	tmp = NULL;
	return (OK);
}

static int	execute_operator(t_tree *operator)
{
	if (operator->tree_type == INPUT)
		return (input_rdt(operator));
	else if (operator->tree_type == OUTPUT)
		return (output_rdt(operator));
	else if (operator->tree_type == APPEND)
		return (rdt_expand(operator));
	else
		return (OTHERS);
}

int	manage_tree_rdt(t_tree *node, t_tree **cmd)
{
	t_tree	*tmp;
	int		count;
	int		index;
	int		status;

	tmp = node;
	*cmd = find_cmd(&tmp, &count);
	if (!cmd && node->right->tree_type == DELIMITER)
		status = 0;
	else
	{
		while (count > 0)
		{
			index = count;
			while (tmp->left && index-- > 1)
				tmp = tmp->left;
			count--;
			status = execute_operator(tmp);
			if (status == KO)
				break ;
			tmp = node;
		}
	}
	return (status);
}
