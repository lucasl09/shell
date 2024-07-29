#include "../../../includes/mandatory/mini_shell.h"
#include <stdio.h>
#include <unistd.h>

static int	validate_export_var(char *str)
{
	int	i;
	int	after_equal;

	i = 0;
	after_equal = FALSE;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (FALSE);
	while (str[i])
	{
		if ((ft_isalnum(str[i]) != 0 || str[i] == '_') && after_equal == FALSE)
			i++;
		else if (str[i] == '=')
		{
			i++;
			after_equal = TRUE;
		}
		else if (after_equal == TRUE)
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

static int	ft_export(char **arg, t_venv **envp, t_venv *env)
{
	int		i;
	int		has_error;

	i = 1;
	has_error = 0;
	if (!arg[1])
		return (ft_envprints(env));
	while (arg[i])
	{
		if (validate_export_var(arg[i]) == TRUE)
			ft_exported_env(arg[i++], envp);
		else
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(arg[i++], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			has_error++;
		}
	}
	if (has_error != 0)
		return (1);
	return (0);
}

int	init_builtins(char **arg, t_data *data, t_venv **envp)
{
	int			status;

	status = ft_changedir(arg, envp);
	if (status != -1)
		return (status);
	if (ft_clear(arg[0]) || ft_echo(arg, data) || call_pwd(arg[0]))
		return (0);
	else if (ft_strncmp(arg[0], "env", 4) == 0)
	{
		if (arg[1] == NULL)
			return (ft_env(envp, FALSE));
		printf("env: ‘%s’: No such file or directory\n", arg[1]);
		return (127);
	}
	else if (ft_strncmp(arg[0], "unset", 6) == 0)
	{
		if (arg[1])
			return (ft_unset(envp, arg[1]));
		else
			return (0);
	}
	else if (ft_strncmp(arg[0], "export", 7) == 0)
		return (ft_export(arg, envp, data->envp));
	return (-1);
}

static int	parse_pipe(const char *input, int sgq, int dbq)
{
	int	index;
	int	valid;

	index = 0;
	valid = 0;
	while (input[index] != '\0')
	{
		if (input[index] == '\'')
			sgq++;
		else if (input[index] == '"')
			dbq++;
		if (input[index] == '|' && !(sgq % 2) && !(dbq % 2))
		{
			if (valid)
				return (0);
			valid = 1;
		}
		else if (ft_isspace(input[index]))
			valid = 0;
		else if (ft_isalnum(input[index]))
			valid = 0;
		index++;
	}
	return (valid);
}

int	has_pipe_in(const char *input)
{
	int	dbq;
	int	sgq;
	int	valid;

	dbq = 0;
	sgq = 0;
	valid = 0;
	if (input[0] == '|')
		return (0);
	valid = parse_pipe(input, sgq, dbq);
	if (valid)
		return (0);
	return (1);
}
