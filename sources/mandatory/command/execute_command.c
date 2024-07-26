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
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

t_tree	*find_cmd(t_tree **root, int *count)
{
	t_tree	*tmp;
	t_tree	*cmd;

	if (!(*root) || !root)
		return (NULL);
	tmp = *root;
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

int	exec_all_ast(t_tree *node, t_data *data, t_tree *cmd, int *fd)
{
	int	status;
	int	fork_cmd;

	status = manage_tree_rdt(node, &cmd);
	if (cmd && status != KO && data->attribute == FALSE)
	{
		fork_cmd = fork();
		if (fork_cmd == 0)
		{
			status = execute_command(cmd, data, &data->envp, LEFT);
			free_storage(&data);
			fkclose(fd, NULL);
			close (STDIN_FILENO);
			close (STDOUT_FILENO);
			exit (status);
		}
		waitpid(fork_cmd, &status, 0);
		status = endpipes(&status, data);
	}
	else if (cmd && status != KO)
		status = execute_command(cmd, data, &data->envp, LEFT);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	fkclose(fd, NULL);
	return (status);
}

int	execute_all_command(t_data *data, t_tree *node)
{
	int		status;
	char	**cmd_args;

	status = 0;
	if (node->left && node->left->tree_type == COMMAND)
		data->direction = LEFT;
	else
		data->direction = RIGHT;
	cmd_args = if_exit_execute(node, data->direction);
	if (cmd_args != NULL)
		return (end_evg(data, &data->envp, cmd_args));
	status = execute_command(node, data, &data->envp, data->direction);
	return (status);
}

int	execute_ast(t_tree *node, t_data *data)
{
	t_tree	*cmd;
	int		fd[2];

	if (node == NULL)
		return (OTHERS);
	cmd = NULL;
	if (node->tree_type == 18)
		return (execute_pipe(node, data));
	else if (node->tree_type >= 14 && node->tree_type < 18)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		return (exec_all_ast(node, data, cmd, fd));
	}
	else
		return (execute_all_command(data, node));
}

int	initialize_execs(t_data *data, t_venv **envp)
{
	t_tree	*root;
	int		status;

	status = 0;
	if (data->tree_lists == NULL || data->tree_lists == NULL)
		return (OTHERS);
	root = data->tree_lists;
	status = find_heredocs(root, data, envp);
	if (status != 0)
	{
		if (status != 130)
		{
			ft_putstr_fd("\033[1;31mMINIHELL>$\033[0m: syntax error ", STDERR_FILENO);
			ft_putstr_fd("near unexpected token `newline'", STDERR_FILENO);
		}
		return (status);
	}
	data->attribute = FALSE;
	data->direction = LEFT;
	if (root->right == NULL && (root->left == NULL || root->left != NULL))
		status = for_each_cmd(root, data, envp);
	else
		status = execute_ast(root, data);
	return (status);
}
