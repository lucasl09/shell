#include <readline/readline.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../../includes/mandatory/mini_shell.h"

static void	for_errors_type(char **cmd_args, char **error_line, \
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

int	execution_error(char **cmd_args, t_venv **envp, int status)
{
	char	*error_line;

	error_line = NULL;
	status = 0;
	if (cmd_args && (cmd_args[0][0] == '/' || (cmd_args[0][0] == '.'
		&& cmd_args[0][1] == '/')))
		for_errors_type(cmd_args, &error_line, &status);
	else
	{
		error_line = ft_strjoin(cmd_args[0], ": command not found");
		status = 127;
	}
	ft_putendl_fd(error_line, 2);
	free(error_line);
	free_trash(cmd_args);
	free_envp(envp);
	rl_clear_history();
	return (status);
}
