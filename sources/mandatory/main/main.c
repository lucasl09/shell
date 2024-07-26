/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:27:05 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/14 17:31:40 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>

volatile int	g_vsig;

void	gprop(int restore)
{
	static struct termios	term;

	if (!restore)
		tcgetattr(STDIN_FILENO, &term);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static int	validate_input(char *input)
{
	int	i;

	if (!input)
	{
		printf("exit\n");
		exit (0);
	}
	if (!ft_strncmp(input, "", 1))
	{
		free (input);
		return (0);
	}
	i = -1;
	while (input[++i])
	{
		if (ft_isspace(input[i]) == 0)
			break ;
	}
	if (input[i] == '\0')
	{
		free (input);
		return (0);
	}
	return (1);
}

static char	*define_user(t_venv **envp, char *tag)
{
	t_venv	*tmp;
	char		*user;

	tmp = env_lstsearch(envp, tag);
	user = NULL;
	if (!tag || !tmp)
		user = ft_strjoin("\033$\033[0m", "/\033[1;31mMINIHELL>$\033[0m  ");
	else
		user = ft_strjoin(tmp->value, "/\033[1;31mMINIHELL>$\033[0m  ");
	tmp = NULL;
	return (user);
}

static int	get_input(t_venv **envp, int status)
{
	char		*input;
	char		*in_user;
	int			valid;

	g_vsig = 0;
	in_user = define_user(envp, "\033USER\033[0m");
	gprop(0);
	input = readline(in_user);
	free(in_user);
	valid = validate_input(input);
	if (valid != TRUE)
		return (valid);
	add_history(input);
	if (!return_checker(input))
	{
		free (input);
		ft_putendl_fd("Error in syntax.", 2);
		return (2);
	}
	return (initialize_mini(envp, input, status));
}

int	main(void)
{
	t_venv	*envp;
	int			status;

	for_signals();
	envp = NULL;
	status = 0;
	get_envp(&envp, __environ);
	while (1)
	{
		status = get_input(&envp, status);
		if (status == 131)
			printf("Quit (core dumped)\n");
		else if ((status == 2 || status == 0) && g_vsig == SIGINT)
		{
			printf("\n");
			status = 130;
		}
		if (status == 131 || (status == 2 && g_vsig == SIGINT))
			gprop(1);
	}
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	free_envp(&envp);
	rl_clear_history();
	return (status);
}
