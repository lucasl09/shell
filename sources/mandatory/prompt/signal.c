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

void	handle_signal(int signum)
{
	(void)signum;
	g_vsig = signum;
}

void	for_signals(void)
{
	signal(SIGINT, handle_new_line);
	signal(SIGQUIT, SIG_IGN);
}


int	inside_heredoc(int inside_heredoc)
{
	static int	heredoc;

	if (inside_heredoc != -1)
		heredoc = inside_heredoc;
	return (heredoc);
}

void	handle_new_line(int signum)
{
	(void)signum;
	g_vsig = signum;
	if (inside_heredoc(-1) == TRUE)
	{
		printf("\n");
		close (STDIN_FILENO);
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_vsig = 0;
	}
}
