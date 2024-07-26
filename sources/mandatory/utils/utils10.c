#include "../../../includes/mandatory/mini_shell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

static char	*build_path(char **path_args, int *index, char **cmd_args)
{
	char	*partial_path;
	char	*path;

	partial_path = ft_strjoin(path_args[(*index)++], "/");
	path = ft_strjoin(partial_path, cmd_args[0]);
	free(partial_path);
	return (path);
}

static char	**build_var_args(t_venv **envp)
{
	t_venv	*temp;
	char		**environ_var;
	int			index;
	int			size_envp;
	char		*line;

	size_envp = env_size(envp);
	environ_var = ft_calloc(sizeof(char *), size_envp + 1);
	temp = *envp;
	index = 0;
	line = NULL;
	while (temp && temp->next && index < size_envp)
	{
		line = ft_strjoin(temp->key, "=");
		environ_var[index] = ft_strjoin(line, temp->value);
		free(line);
		temp = temp->next;
		index++;
	}
	return (environ_var);
}

static void	for_errors_status(char **cmd_args, char **error_line, \
									int *status)
{
	struct stat	sb;

	if (stat(cmd_args[0], &sb) == 0)
	{
		if ((sb.st_mode & S_IFMT) == S_IFDIR)
		{
			*error_line = ft_strjoin(cmd_args[0], ": Is a directory");
			*status = 126;
		}
		else
			*error_line = ft_strjoin(cmd_args[0],
					": No such file or directory");
	}
	else
	{
		*error_line = ft_strjoin(cmd_args[0], ": No such file or directory");
		*status = 127;
	}
	if (cmd_args[0][0] == '/' && *status == 0)
		*status = 127;
	else if (status == 0)
		*status = 126;
}

int	for_errors(char **cmd_args, t_venv **envp, int status)
{
	char	*error_line;

	error_line = NULL;
	status = 0;
	if (cmd_args && (cmd_args[0][0] == '/' || (cmd_args[0][0] == '.'
		&& cmd_args[0][1] == '/')))
		for_errors_status(cmd_args, &error_line, &status);
	else
	{
		error_line = ft_strjoin(cmd_args[0], ": command not found");
		status = 127;
	}
	ft_putendl_fd(error_line, 2);
	free(error_line);
	free_evg(cmd_args);
	free_envp(envp);
	rl_clear_history();
	return (status);
}

static int	try_path(char **cmd_args, char **path_args, char **args, int *index)
{
	char	*path;
	int		status;

	if (*index == -1)
		path = ft_strdup(cmd_args[++(*index)]);
	else
		path = build_path(path_args, index, cmd_args);
	status = access(path, F_OK | X_OK);
	if (status == 0)
	{
		status = execve(path, cmd_args, args);
		if (status == -1)
			status = KO;
	}
	else if (status != 0 && (cmd_args[0][0] == '.' || cmd_args[0][0] == '/'))
	{
		if (access(path, F_OK) != 0)
			status = 127;
		else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
			status = 126;
	}
	free(path);
	return (status);
}

static void	start_execution(char **cmd_args, char **path_args, int *status,
		t_venv **envp)
{
	char	*temp;
	char	*final;
	int		index;
	char	**args;

	index = -1;
	args = build_var_args(envp);
	while (index == -1 || path_args[index])
	{
		*status = try_path(cmd_args, path_args, args, &index);
		if (*status == KO || *status == 127)
			break ;
		else if (*status == 126)
		{
			temp = ft_strjoin("minishell: ", cmd_args[0]);
			final = ft_strjoin(temp, ": Permission denied\n");
			ft_putstr_fd(final, STDERR_FILENO);
			free(temp);
			free(final);
			free_evg(cmd_args);
			return ;
		}
	}
	free_onlyargs(path_args, args);
}

int	execute_command(t_tree *node, t_data *data, t_venv **envp, int direction)
{
	char	**cmd_args;
	char	**path_args;
	int		status;

	cmd_args = get_cmd_args(node, direction);
	status = initialize_builtins(cmd_args, data, envp);
	signal(SIGQUIT, SIG_DFL);
	if (status != -1)
	{
		tree_clear(&data->tree_lists);
		free_envp(&data->envp);
		free(data);
		rl_clear_history();
		free_evg(cmd_args);
		exit(status);
	}
	if (cmd_args[0][0] == '\'' || cmd_args[0][0] == '\"')
		return (for_errors(cmd_args, &data->envp, 0));
	path_args = get_path(envp, "PATH", cmd_args[0]);
	start_execution(cmd_args, path_args, &status, envp);
	signal(SIGQUIT, SIG_IGN);
	if (status == 126)
		return (126);
	return (for_errors(cmd_args, &data->envp, status));
}
