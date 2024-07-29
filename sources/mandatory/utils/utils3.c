/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:12:33 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/13 15:12:35 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

static int	exit_status_mini(char *input)
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
			temp = ft_strjoin("minihell: exit: ", input);
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

void	error_mini(char **all_args)
{
	ft_putendl_fd("exit", 1);
	ft_putendl_fd("minihell: exit: too many arguments", STDERR_FILENO);
	free_trash(all_args);
	return ;
}

int	exit_minihell(t_data *data, t_venv **envp, char **cmd_args)
{
	int	status;

	status = 0;
	if (ft_strncmp(cmd_args[0], "exit", 5) == 0 && cmd_args[1] == NULL)
		status = 0;
	else if (ft_strncmp(cmd_args[0], "exit", 5) == 0 && cmd_args[1] != NULL)
		status = exit_status_mini(cmd_args[1]);
	if (ft_strncmp(cmd_args[0], "exit", 5) == 0 && cmd_args[1] != NULL
		&& cmd_args[2] != NULL && status != 2)
	{
		error_mini(cmd_args);
		return (1);
	}
	free_trash(cmd_args);
	ft_putendl_fd("exit", 1);
	if (data->attribute == FALSE)
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
				return (FAILED);
			i++;
		}
		return (SUCESS);
	}
	else
		return (FAILED);
}

char	**if_exited(t_tree *node, int direction)
{
	char	**cmd_args;

	if (node->tree_type != COMMAND)
		node = node->right;
	cmd_args = get_cmd_args(node, direction);
	if (ft_strncmp(cmd_args[0], "exit", 5))
	{
		free_trash(cmd_args);
		return (NULL);
	}
	return (cmd_args);
}
