/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:40 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/13 16:17:51 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

static int	child_process(t_tree *node, t_data *data, t_venv **envp)
{
	int	status;

	status = 0;
	status = execute_command(node, data, envp, LEFT);
	tree_clear(&node);
	data->envp = NULL;
	free(data);
	data = NULL;
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	return (status);
}

static int	parent_process(t_data *data, pid_t pid, int status)
{
	data->envp = NULL;
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

static int	check_builtins(t_tree *node, t_data *data, t_venv **envp)
{
	char	**cmd_args;
	int		status;

	status = 0;
	cmd_args = if_exit_execute(node, LEFT);
	if (cmd_args != NULL)
		return (end_evg(data, envp, cmd_args));
	cmd_args = get_cmd_args(node, LEFT);
	status = initialize_builtins(cmd_args, data, envp);
	if (status != -1)
	{
		free_evg(cmd_args);
		return (status);
	}
	free_evg(cmd_args);
	return (status);
}

int	for_each_cmd(t_tree *node, t_data *data, t_venv **envp)
{
	pid_t	pid;
	int		status;

	status = check_builtins(node, data, envp);
	if (status != -1)
		return (status);
	status = 0;
	signal(SIGINT, handle_signal);
	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		exit(child_process(node, data, envp));
	else
		return (parent_process(data, pid, status));
}
