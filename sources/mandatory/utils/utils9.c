#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include "../../../includes/mandatory/mini_shell.h"


static int	end_evg_status(char *input)
{
	int		i;
	char	*tmp;
	char	*final;

	i = 0;
	if (input[0] == '-')
		return (156);
	else if (input[0] == '+')
		i++;
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
		{
			tmp = ft_strjoin("minishell: exit: ", input);
			final = ft_strjoin(tmp, ": numeric argument required");
			free(tmp);
			ft_putendl_fd(final, STDERR_FILENO);
			free(final);
			return (2);
		}
		i++;
	}
	return (ft_atoi(input));
}

void	end_evg_error(char **all_args)
{
	ft_putendl_fd("exit", 1);
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	free_args(all_args);
	return ;
}

int	end_evg(t_data *data, t_venv **envp, char **has_arg)
{
	int	status;

	status = 0;
	if (ft_strncmp(has_arg[0], "exit", 5) == 0 && has_arg[1] == NULL)
		status = 0;
	else if (ft_strncmp(has_arg[0], "exit", 5) == 0 && has_arg[1] != NULL)
		status = end_evg_status(has_arg[1]);
	if (ft_strncmp(has_arg[0], "exit", 5) == 0 && has_arg[1] != NULL
		&& has_arg[2] != NULL && status != 2)
	{
		end_evg_error(has_arg);
		return (1);
	}
	free_args(has_arg);
	ft_putendl_fd("exit", 1);
	if (data->check_opr == FT_ERROR)
	{
		free_envp(envp);
		rl_clear_history();
		free_data(&data);
		exit(status);
	}
	return (status);
}

int	check_exit(char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]) == 1)
		i++;
	if (ft_strncmp(&(input[i]), "exit", 4) == 0)
	{
		while (input[i + 4])
		{
			if (ft_isalnum(input[i + 4]) == 0 && ft_isspace(input[i + 4]) == 0)
				return (FT_ERROR);
			i++;
		}
		return (SUCESS);
	}
	else
		return (FT_ERROR);
}

char	**exit_checkerexec(t_tree *node, int direction)
{
	char	**has_arg;

	if (node->tree_type != COMMAND)
		node = node->right;
	has_arg = get_has_arg(node, direction);
	if (ft_strncmp(has_arg[0], "exit", 5))
	{
		free_args(has_arg);
		return (NULL);
	}
	return (has_arg);
}