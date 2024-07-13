/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:15:28 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/15 16:08:06 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	afterprompt(int is_after)
{
	static int	after;

	if (is_after != -1)
		after = is_after;
	return (after);
}

void	handle_signal(int signum)
{
	if (isatty(STDIN_FILENO))
	{
		if (signum == SIGINT)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			ft_putstr_fd("\n", 2);
			if (!afterprompt(-1))
				rl_redisplay();
		}
		else if (signum == SIGQUIT)
		{
		}
		else if (signum == SIGTERM)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
	}
}
