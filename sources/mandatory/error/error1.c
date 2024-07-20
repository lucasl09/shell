#include <readline/readline.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../../includes/mandatory/mini_shell.h"
#include <fcntl.h>
#include <linux/stat.h>
#include <sys/types.h>
#include <sys/stat.h>

static void	show_errors_status(char **has_arg, char **error_line, \
									int *status)
{
	struct stat	sb;

	if (stat(has_arg[0], &sb) == 0)
	{
		if ((sb.st_mode & S_IFMT) == S_IFDIR)
		{
			*error_line = ft_strjoin(has_arg[0], ": Is a directory");
			*status = 126;
		}
		else
			*error_line = ft_strjoin(has_arg[0],
					": No such file or directory");
	}
	else
	{
		*error_line = ft_strjoin(has_arg[0], ": No such file or directory");
		*status = 127;
	}
	if (has_arg[0][0] == '/' && *status == 0)
		*status = 127;
	else if (status == 0)
		*status = 126;
}

int	show_errors(char **has_arg, t_venv **envp, int status)
{
	char	*error_line;

	error_line = NULL;
	status = 0;
	if (has_arg && (has_arg[0][0] == '/' || (has_arg[0][0] == '.'
		&& has_arg[0][1] == '/')))
		show_errors_status(has_arg, &error_line, &status);
	else
	{
		error_line = ft_strjoin(has_arg[0], ": command not found");
		status = 127;
	}
	ft_putendl_fd(error_line, 2);
	free(error_line);
	free_args(has_arg);
	free_envp(envp);
	rl_clear_history();
	return (status);
}