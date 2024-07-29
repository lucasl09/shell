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
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	put_redirect_in(t_tree *opr)
{
	t_tree	*tmp;
	int		file_fd;

	tmp = opr->right;
	file_fd = open(tmp->content, O_RDONLY);
	if (file_fd == -1)
	{
		fkclose(&file_fd, "minishell");
		return (FAILED);
	}
	if (dup2(file_fd, STDIN_FILENO) == -1)
	{
		fkclose(&file_fd, "minishell");
		return (FAILED);
	}
	close(file_fd);
	tmp = NULL;
	return (SUCESS);
}

int	put_redirect_out(t_tree *opr)
{
	t_tree	*tmp;
	int		file_fd;

	tmp = opr->right;
	file_fd = open(tmp->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file_fd == -1)
	{
		fkclose(&file_fd, "minishell");
		return (FAILED);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		fkclose(&file_fd, "minishell");
		return (FAILED);
	}
	close(file_fd);
	tmp = NULL;
	return (SUCESS);
}

int	append_redirects(t_tree *opr)
{
	t_tree	*tmp;
	int		file_fd;

	tmp = opr->right;
	file_fd = open(tmp->content, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file_fd == -1)
	{
		fkclose(&file_fd, "minihell");
		return (FAILED);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		fkclose(&file_fd, "minihell");
		return (FAILED);
	}
	close(file_fd);
	tmp = NULL;
	return (SUCESS);
}

static int	exec_opr(t_tree *opr)
{
	if (opr->tree_type == INPUT)
		return (put_redirect_in(opr));
	else if (opr->tree_type == OUTPUT)
		return (put_redirect_out(opr));
	else if (opr->tree_type == APPEND)
		return (append_redirects(opr));
	else
		return (NFOUND);
}

int	rltree_redirect(t_tree *node, t_tree **cmd)
{
	t_tree	*tmp;
	int		count;
	int		index;
	int		status;

	tmp = node;
	*cmd = foundedcmd(&tmp, &count);
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
			status = exec_opr(tmp);
			if (status == FAILED)
				break ;
			tmp = node;
		}
	}
	return (status);
}
