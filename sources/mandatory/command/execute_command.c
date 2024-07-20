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

static char	**initialize_varg(t_venv **envp)
{
	t_venv	*tmp;
	char		**environ_var;
	int			index;
	int			size_envp;
	char		*line;

	size_envp = env_size(envp);
	environ_var = ft_calloc(sizeof(char *), size_envp + 1);
	tmp = *envp;
	index = 0;
	line = NULL;
	while (tmp && tmp->next && index < size_envp)
	{
		line = ft_strjoin(tmp->key, "=");
		environ_var[index] = ft_strjoin(line, tmp->value);
		free(line);
		tmp = tmp->next;
		index++;
	}
	return (environ_var);
}

static char	*build_path(char **path_args, int *index, char **has_arg)
{
	char	*partial_path;
	char	*path;

	partial_path = ft_strjoin(path_args[(*index)++], "/");
	path = ft_strjoin(partial_path, has_arg[0]);
	free(partial_path);
	return (path);
}

static int	repath(char **has_arg, char **path_args, char **args, int *index)
{
	char	*path;
	int		status;

	if (*index == -1)
		path = ft_strdup(has_arg[++(*index)]);
	else
		path = build_path(path_args, index, has_arg);
	status = access(path, F_OK | X_OK);
	if (status == 0)
	{
		status = execve(path, has_arg, args);
		if (status == -1)
			status = FT_ERROR;
	}
	else if (status != 0 && (has_arg[0][0] == '.' || has_arg[0][0] == '/'))
	{
		if (access(path, F_OK) != 0)
			status = 127;
		else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
			status = 126;
	}
	free(path);
	return (status);
}

static void	start_execution(char **has_arg, char **path_args, int *status,
		t_venv **envp)
{
	char	*tmp;
	char	*final;
	int		index;
	char	**args;

	index = -1;
	args = initialize_varg(envp);
	while (index == -1 || path_args[index])
	{
		*status = repath(has_arg, path_args, args, &index);
		if (*status == FT_ERROR || *status == 127)
			break ;
		else if (*status == 126)
		{
			tmp = ft_strjoin("minishell: ", has_arg[0]);
			final = ft_strjoin(tmp, ": Permission denied\n");
			ft_putstr_fd(final, STDERR_FILENO);
			free(tmp);
			free(final);
			free_args(has_arg);
			return ;
		}
	}
	free_ptargs(path_args, args);
}

int	execute_command(t_tree *node, t_data *data, t_venv **envp, int direction)
{
	char	**has_arg;
	char	**path_args;
	int		status;

	has_arg = get_has_arg(node, direction);
	status = builtins(has_arg, data, envp);
	signal(SIGQUIT, SIG_DFL);
	if (status != -1)
	{
		treelst_clear(&data->tree_lists);
		free_envp(&data->envp);
		free(data);
		rl_clear_history();
		free_args(has_arg);
		exit(status);
	}
	if (has_arg[0][0] == '\'' || has_arg[0][0] == '\"')
		return (show_errors(has_arg, &data->envp, 0));
	path_args = get_path(envp, "PATH", has_arg[0]);
	start_execution(has_arg, path_args, &status, envp);
	signal(SIGQUIT, SIG_IGN);
	if (status == 126)
		return (126);
	return (show_errors(has_arg, &data->envp, status));
}
