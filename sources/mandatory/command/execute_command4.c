#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include "../../../includes/mandatory/mini_shell.h"

static int	child_process(t_tree *node, t_data *data, t_venv **envp)
{
	int	status;

	status = 0;
	status = execute_command(node, data, envp, TO_LEFT);
	tree_listsclear(&node);
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
	char	**has_arg;
	int		status;

	status = 0;
	has_arg = exit_checkerexec(node, TO_LEFT);
	if (has_arg != NULL)
		return (end_evg(data, envp, has_arg));
	has_arg = get_has_arg(node, TO_LEFT);
	// status = builtins(has_arg, data, envp);
	if (status != -1)
	{
		free_args(has_arg);
		return (status);
	}
	free_args(has_arg);
	return (status);
}

int	ongoing_cmds(t_tree *node, t_data *data, t_venv **envp)
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
