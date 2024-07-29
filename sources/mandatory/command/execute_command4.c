#include "../../../includes/mandatory/mini_shell.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

static int	child_process(t_tree *node, t_data *data, t_venv **envp)
{
	int	status;

	status = 0;
	status = execute_command(node, data, envp, LEFT);
	treelst_clear(&node);
	data->envp = NULL;
	free(data);
	data = NULL;
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	return (status);
}

static int	is_family(t_data *data, pid_t pid, int status)
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

static int	if_cbuiltins(t_tree *node, t_data *data, t_venv **envp)
{
	char	**cmd_args;
	int		status;

	status = 0;
	cmd_args = if_exited(node, LEFT);
	if (cmd_args != NULL)
		return (exit_minihell(data, envp, cmd_args));
	cmd_args = get_cmd_args(node, LEFT);
	status = init_builtins(cmd_args, data, envp);
	if (status != -1)
	{
		free_trash(cmd_args);
		return (status);
	}
	free_trash(cmd_args);
	return (status);
}

int	executables_init(t_tree *node, t_data *data, t_venv **envp)
{
	pid_t	pid;
	int		status;

	status = if_cbuiltins(node, data, envp);
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
		return (is_family(data, pid, status));
}
