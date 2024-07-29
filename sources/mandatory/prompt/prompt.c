/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:05:13 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/14 16:47:58 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

static t_data	*force_init_data(int status)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_list = NULL;
	data->tree_listed = NULL;
	data->envp = NULL;
	data->endsts = status;
	data->has_env = FALSE;
	return (data);
}

static int	force_bdata(t_data *data, t_venv **envp, char *input)
{
	if (build_token(input, &data->token_list) == ERROR)
		return (0);
	data->token_list = manage_tlists(data, envp);
	if (data->token_list == NULL)
	{
		free_data(&data);
		return (0);
	}
	eotokens(&data->token_list, &data->tree_listed);
	if (!data->tree_listed)
		return (0);
	tokenlst_clear(&data->token_list);
	data->envp = *envp;
	return (1);
}

int	init_minihell(t_venv **envp, char *input, int status)
{
	t_data	*data;

	data = force_init_data(status);
	signal(SIGINT, sig_newline);
	if (!force_bdata(data, envp, input))
		return (0);
	status = ongoing_exec(data, envp);
	signal(SIGINT, sig_newline);
	release_heredoc(data->tree_listed);
	if (data)
		free_data(&data);
	return (status);
}

void	initialize(void)
{
	printf("\033[1;33mALL DONE\033[0m\n");
	printf("\033[1;33mMINIHELL started!\033[0m\n");
}
