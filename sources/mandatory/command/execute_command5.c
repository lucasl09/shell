#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../../includes/mandatory/mini_shell.h"

int	open_redir_input(t_tree *operator)
{
	t_tree	*tmp;
	int		file_fd;

	tmp = operator->right;
	file_fd = open(tmp->content, O_RDONLY);
	if (file_fd == -1)
	{
		fkclose(&file_fd, "minishell");
		return (CERROR);
	}
	if (dup2(file_fd, STDIN_FILENO) == -1)
	{
		fkclose(&file_fd, "minishell");
		return (CERROR);
	}
	close(file_fd);
	tmp = NULL;
	return (SUCESS);
}

int	open_redir_output(t_tree *operator)
{
	t_tree	*tmp;
	int		file_fd;

	tmp = operator->right;
	file_fd = open(tmp->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file_fd == -1)
	{
		fkclose(&file_fd, "minishell");
		return (CERROR);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		fkclose(&file_fd, "minishell");
		return (CERROR);
	}
	close(file_fd);
	tmp = NULL;
	return (SUCESS);
}

int	open_redir_append(t_tree *operator)
{
	t_tree	*tmp;
	int		file_fd;

	tmp = operator->right;
	file_fd = open(tmp->content, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file_fd == -1)
	{
		fkclose(&file_fd, "minishell");
		return (CERROR);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		fkclose(&file_fd, "minishell");
		return (CERROR);
	}
	close(file_fd);
	tmp = NULL;
	return (SUCESS);
}

static int	execute_opr(t_tree *operator)
{
	if (operator->tree_type == INPUT)
		return (open_redir_input(operator));
	else if (operator->tree_type == OUTPUT)
		return (open_redir_output(operator));
	else if (operator->tree_type == APPEND)
		return (open_redir_append(operator));
	else
		return (EMPTY);
}

int	consume_rdirect(t_tree *node, t_tree **cmd)
{
	t_tree	*tmp;
	int		count;
	int		index;
	int		status;

	tmp = node;
	*cmd = find_cmd(&tmp, &count);
	if (!cmd && node->right->tree_type == DELIMITER)
		status = 0;
	else
	{
		while (count > 0)
		{
			index = count;
			while (tmp->left && index-- > 1)
				tmp = tmp->left;
			count--;
			status = execute_opr(tmp);
			if (status == CERROR)
				break ;
			tmp = node;
		}
	}
	return (status);
}
