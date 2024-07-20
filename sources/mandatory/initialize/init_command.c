#include "../../../includes/mandatory/mini_shell.h"

t_tree	*cmd_found(t_tree **stm, int *count)
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

int	execute_mult_tree(t_tree *node, t_data *data, t_tree *cmd, int *fd)
{
	int	status;
	int	fkcmd;

	status = consume_rdirect(node, &cmd);
	if (cmd && status != FT_ERROR && data->check_opr == FT_ERROR)
	{
		fkcmd = fork();
		if (fkcmd == 0)
		{
			status = execute_command(cmd, data, &data->envp, TO_LEFT);
			free_data(&data);
			fkclose(fd, NULL);
			close (STDIN_FILENO);
			close (STDOUT_FILENO);
			exit (status);
		}
		waitpid(fkcmd, &status, 0);
		status = finish_pipe(&status, data);
	}
	else if (cmd && status != FT_ERROR)
		status = execute_command(cmd, data, &data->envp, TO_LEFT);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	fkclose(fd, NULL);
	return (status);
}

int	initialize_cmdexec(t_data *data, t_tree *node)
{
	int		status;
	char	**has_arg;

	status = 0;
	if (node->left && node->left->tree_type == COMMAND)
		data->direction = TO_LEFT;
	else
		data->direction = TO_RIGHT;
	has_arg = exit_checkerexec(node, data->direction);
	if (has_arg != NULL)
		return (end_evg(data, &data->envp, has_arg));
	status = execute_command(node, data, &data->envp, data->direction);
	return (status);
}

int	ongoing_exectree(t_tree *node, t_data *data)
{
	t_tree	*cmd;
	int		fd[2];

	if (node == NULL)
		return (EMPTY);
	cmd = NULL;
	if (node->tree_type == 18)
		return (execute_pipe(node, data));
	else if (node->tree_type >= 14 && node->tree_type < 18)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		return (execute_mult_tree(node, data, cmd, fd));
	}
	else
		return (initialize_cmdexec(data, node));
}

int	cmds_start(t_data *data, t_venv **envp)
{
	t_tree	*stm;
	int		status;

	status = 0;
	if (data->tree_lists == NULL || data->tree_lists == NULL)
		return (EMPTY);
	stm = data->tree_lists;
	status = heredoc_delimiter(stm, data, envp);
	if (status != 0)
	{
		if (status != 130)
		{
			ft_putstr_fd("minishell: syntax error ", STDERR_FILENO);
			ft_putstr_fd("near unexpected token `newline'", STDERR_FILENO);
		}
		return (status);
	}
	data->check_opr = FT_ERROR;
	data->direction = TO_LEFT;
	if (stm->right == NULL && (stm->left == NULL || stm->left != NULL))
		status = ongoing_cmds(stm, data, envp);
	else
		status = ongoing_exectree(stm, data);
	return (status);
}