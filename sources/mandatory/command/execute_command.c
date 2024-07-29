/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:48:42 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/14 16:10:08 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

t_tree	*foundedcmd(t_tree **stm, int *count)
{
	t_tree	*tmp;
	t_tree	*cmd;

	if (!(*stm) || !stm)
		return (NULL);
	tmp = *stm;
	cmd = NULL;
	(*count) = 0;
	while (tmp && tmp->tree_type != COMMAND)
	{
		(*count)++;
		tmp = tmp->left;
	}
	if (!tmp)
		return (NULL);
	cmd = tmp;
	tmp = NULL;
	return (cmd);
}

int	force_tree_exec(t_tree *node, t_data *data, t_tree *cmd, int *fd)
{
	int	status;
	int	fork_cmd;

	status = rltree_redirect(node, &cmd);
	if (cmd && status != FAILED && data->attribute == FALSE)
	{
		fork_cmd = fork();
		if (fork_cmd == 0)
		{
			status = execute_command(cmd, data, &data->envp, LEFT);
			free_data(&data);
			fkclose(fd, NULL);
			close (STDIN_FILENO);
			close (STDOUT_FILENO);
			exit (status);
		}
		waitpid(fork_cmd, &status, 0);
		status = endpipes(&status, data);
	}
	else if (cmd && status != FAILED)
		status = execute_command(cmd, data, &data->envp, LEFT);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	fkclose(fd, NULL);
	return (status);
}

int	exec_full(t_data *data, t_tree *node)
{
	int		status;
	char	**cmd_args;

	status = 0;
	if (node->left && node->left->tree_type == COMMAND)
		data->direction = LEFT;
	else
		data->direction = RIGHT;
	cmd_args = if_exited(node, data->direction);
	if (cmd_args != NULL)
		return (exit_minihell(data, &data->envp, cmd_args));
	status = execute_command(node, data, &data->envp, data->direction);
	return (status);
}

int	initialize_trees(t_tree *node, t_data *data)
{
	t_tree	*cmd;
	int		fd[2];

	if (node == NULL)
		return (NFOUND);
	cmd = NULL;
	if (node->tree_type == 18)
		return (execute_pipe(node, data));
	else if (node->tree_type >= 14 && node->tree_type < 18)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		return (force_tree_exec(node, data, cmd, fd));
	}
	else
		return (exec_full(data, node));
}

int	ongoing_exec(t_data *data, t_venv **envp)
{
	t_tree	*stm;
	int		status;

	status = 0;
	if (data->tree_listed == NULL || data->tree_listed == NULL)
		return (NFOUND);
	stm = data->tree_listed;
	status = founded_hd(stm, data, envp);
	if (status != 0)
	{
		if (status != 130)
		{
			ft_putstr_fd("minihell: syntax error ", STDERR_FILENO);
			ft_putstr_fd("near unexpected token `newline'", STDERR_FILENO);
		}
		return (status);
	}
	data->attribute = FALSE;
	data->direction = LEFT;
	if (stm->right == NULL && (stm->left == NULL || stm->left != NULL))
		status = executables_init(stm, data, envp);
	else
		status = initialize_trees(stm, data);
	return (status);
}
