#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include "../../../includes/mandatory/mini_shell.h"

static void	exec_child_one(t_data *data, t_tree *node)
{
	int	status;

	status = 0;
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		fkclose(data->pipe_fd, "pipe");
		exit(EXIT_FAILURE);
	}
	close(data->pipe_fd[1]);
	close(data->pipe_fd[0]);
	rl_clear_history();
	data->attribute = TRUE;
	data->direction = LEFT;
	status = execute_ast(node->left, data);
	tree_clear(&data->tree_lists);
	env_lstclear(&data->envp);
	free(data);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	if (status == KO)
		exit(EXIT_FAILURE);
	exit(status);
}

static void	exec_child_two(t_data *data, t_tree *node)
{
	int	status;

	status = 0;
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
	{
		fkclose(data->pipe_fd, "pipe");
		exit(EXIT_FAILURE);
	}
	fkclose(data->pipe_fd, NULL);
	rl_clear_history();
	data->attribute = TRUE;
	data->direction = RIGHT;
	status = execute_ast(node->right, data);
	tree_clear(&data->tree_lists);
	env_lstclear(&data->envp);
	free(data);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (status == KO)
		exit(EXIT_FAILURE);
	exit(status);
}

int	endpipes(int *status, t_data *data)
{
	if (data->tree_lists)
		tree_clear(&data->tree_lists);
	if (data->token_list)
		clear_tokens(&data->token_list);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	return (*status);
}

int	execute_pipe(t_tree *node, t_data *data)
{
	int	status;

	status = 0;
	signal(SIGINT, handle_signal);
	if (pipe(data->pipe_fd) == 0)
	{
		data->fork[0] = fork();
		if (data->fork[0] == 0)
			exec_child_one(data, node);
		data->fork[1] = fork();
		if (data->fork[1] == 0)
			exec_child_two(data, node);
		fkclose(data->pipe_fd, NULL);
		waitpid(data->fork[0], &status, 0);
		waitpid(data->fork[1], &status, 0);
	}
	return (endpipes(&status, data));
}
