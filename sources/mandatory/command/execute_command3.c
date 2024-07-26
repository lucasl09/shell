#include <readline/readline.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../../includes/mandatory/mini_shell.h"

static int	end_evg_status(char *input)
{
	int		i;
	char	*temp;
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
			temp = ft_strjoin("\033[1;31mMINIHELL>$\033[0m: exit: ", input);
			final = ft_strjoin(temp, ": numeric argument required");
			free(temp);
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
	ft_putendl_fd("\033[1;31mMINIHELL>$\033[0m: exit: too many arguments", STDERR_FILENO);
	free_evg(all_args);
	return ;
}

int	end_evg(t_data *data, t_venv **envp, char **cmd_args)
{
	int	status;

	status = 0;
	if (ft_strncmp(cmd_args[0], "exit", 5) == 0 && cmd_args[1] == NULL)
		status = 0;
	else if (ft_strncmp(cmd_args[0], "exit", 5) == 0 && cmd_args[1] != NULL)
		status = end_evg_status(cmd_args[1]);
	if (ft_strncmp(cmd_args[0], "exit", 5) == 0 && cmd_args[1] != NULL
		&& cmd_args[2] != NULL && status != 2)
	{
		end_evg_error(cmd_args);
		return (1);
	}
	free_evg(cmd_args);
	ft_putendl_fd("exit", 1);
	if (data->attribute == FALSE)
	{
		free_envp(envp);
		rl_clear_history();
		free_storage(&data);
		exit(status);
	}
	return (status);
}

int	if_exit(char *input)
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
				return (KO);
			i++;
		}
		return (OK);
	}
	else
		return (KO);
}

char	**if_exit_execute(t_tree *node, int direction)
{
	char	**cmd_args;

	if (node->tree_type != COMMAND)
		node = node->right;
	cmd_args = get_cmd_args(node, direction);
	if (ft_strncmp(cmd_args[0], "exit", 5))
	{
		free_evg(cmd_args);
		return (NULL);
	}
	return (cmd_args);
}
