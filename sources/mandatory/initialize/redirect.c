#include "../../../includes/mandatory/mini_shell.h"

void	init_redirect(t_tree *opr, int fd, int redirect)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork!");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (dup2(fd, redirect) == -1)
		{
			perror("Failed to redirect!");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
		execute_command(opr->content);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
}

int	init_redirect_input(t_tree *opr)
{
	int	fd;

	fd = open(opr->right->content, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file!");
		return (KO);
	}
	init_redirect(opr->left, fd, STDIN_FILENO);
	close (fd);
	return (SUCESS);
}

int	init_redirect_output(t_tree *opr)
{
	int		fd;

	fd = open(opr->right->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Failed to open file!");
		return (KO);
	}
	init_redirect(opr->left, fd, STDOUT_FILENO);
	close (fd);
	return (SUCESS);
}

int	init_redirect_append(t_tree *opr)
{
	
	int		fd;

	fd = open(opr->right->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Failed to open file!");
		return (KO);
	}
	init_redirect(opr->left, fd, STDOUT_FILENO);
	close (fd);
	return (SUCESS);
}
