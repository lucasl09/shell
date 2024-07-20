#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include "../../../includes/mandatory/mini_shell.h"

static void	exchild(t_data *data, t_tree *node)
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
	data->check_opr = TRUE;
	data->direction = TO_LEFT;
	status = ongoing_exectree(node->left, data);
	tree_listsclear(&data->tree_lists);
	env_lstclear(&data->envp);
	free (data);
	close (STDOUT_FILENO);
	close (STDIN_FILENO);
	if (status == FT_ERROR)
		exit (EXIT_FAILURE);
	exit(status);
}

static void	exchild_tmp(t_data *data, t_tree *node)
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
	data->check_opr = TRUE;
	data->direction = TO_RIGHT;
	status = ongoing_exectree(node->right, data);
	tree_listsclear(&data->tree_lists);
	env_lstclear(&data->envp);
	free (data);
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	if (status == FT_ERROR)
		exit (EXIT_FAILURE);
	exit(status);
}

int	finish_pipe(int *status, t_data *data)
{
	if (data->tree_lists)
		treelst_sclear(&data->tree_lists);
	if (data->token_list)
		clear_tokens(&data->token_list);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	return (*status);
}

int	execute_pipe(t_tree *node, t_data *data)
{
	int			status;
	char		**has_arg;

	status = 0;
	signal(SIGINT, handle_signal);
	has_arg = NULL;
	if (pipe(data->pipe_fd) == 0)
	{
		data->fork[0] = fork();
		if (data->fork[0] == 0)
			exchild(data, node);
		data->fork[1] = fork();
		if (data->fork[1] == 0)
			exchild_tmp(data, node);
		fkclose(data->pipe_fd, NULL);
		waitpid(data->fork[0], &status, 0);
		waitpid(data->fork[1], &status, 0);
	}
	return (finish_pipe(&status, data));
}
