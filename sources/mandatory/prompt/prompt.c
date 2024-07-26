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

static t_data	*initialize_data(int status)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_list = NULL;
	data->tree_lists = NULL;
	data->envp = NULL;
	data->for_sts = status;
	data->has_env = FALSE;
	return (data);
}

static int	build_data_storage(t_data *data, t_venv **envp, char *input)
{
	if (create_token(input, &data->token_list) == ERROR)
		return (0);
	data->token_list = add_tlist(data, envp);
	if (data->token_list == NULL)
	{
		free_storage(&data);
		return (0);
	}
	eotokens(&data->token_list, &data->tree_lists);
	if (!data->tree_lists)
		return (0);
	clear_tokens(&data->token_list);
	data->envp = *envp;
	return (1);
}

int	initialize_mini(t_venv **envp, char *input, int status)
{
	t_data	*data;

	data = initialize_data(status);
	signal(SIGINT, putnewline);
	if (!build_data_storage(data, envp, input))
		return (0);
	status = initialize_execs(data, envp);
	signal(SIGINT, putnewline);
	find_hd_delimiter(data->tree_lists);
	if (data)
		free_storage(&data);
	return (status);
}

