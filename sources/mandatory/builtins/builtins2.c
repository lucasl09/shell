/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:29:34 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/14 15:54:00 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	ft_pwd(char *input)
{
	char	*pwd;

	if (ft_strncmp(input, "pwd", 4))
		return (0);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (1);
}

static void	chand_env_pwd(t_venv **envp)
{
	t_venv	*temp;
	t_venv	*pwd;

	temp = env_lstsearch(envp, ("OLDPWD"));
	pwd = env_lstsearch(envp, ("PWD"));
	free(temp->value);
	temp->value = ft_strdup(pwd->value);
	temp = NULL;
	free(pwd->value);
	pwd->value = getcwd(NULL, 0);
	pwd = NULL;
}

static int	valid_cd(t_venv **envp, char *input)
{
	t_venv	*path;
	int			status;

	path = env_lstsearch(envp, "HOME");
	if (input)
		status = chdir(input);
	else
		status = chdir(path->value);
	if (status == -1)
	{
		path = NULL;
		perror("cd");
		return (1);
	}
	path = NULL;
	chand_env_pwd(envp);
	return (0);
}

int	ft_cd(char **input, t_venv **envp)
{
	if (ft_strncmp(input[0], "cd", 3))
		return (-1);
	if (!input[1])
		return (valid_cd(envp, NULL));
	else if (input[2])
	{
		ft_putstr_fd("/\033[1;31mMINIHELL>$\033[0m: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (valid_cd(envp, input[1]));
}

int	ft_clear(char *input)
{
	if (ft_strncmp(input, "clear", 6) == 0)
	{
		ft_putendl_fd("\e[2J\e[H", 1);
		return (1);
	}
	return (0);
}
