/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:05:13 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/15 16:52:45 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int		prompt(void)
{
	char		*input;
	t_token		*tokens;
	t_tree		*in_tree;

	initialize_lists(&tokens, &in_tree);
	input = readline("\033[1;31mMINIHELL>$\033[0m ");
	if (!ft_strncmp(input, "", 1))
		return (0);
	add_history(input);
	if (initialize_checker(input))
	{
		if (initialize_buildtoken(input, &tokens) == ERROR)
			return (0);
		eotokens(&tokens, &in_tree);
		// if (builtins(tokens))
			return (1);
		initialize_execution(&in_tree, &tokens);
		free (input);
	}
	else
	{
		ft_putendl_fd("Error in syntax.", 2);
		return (0);
	}
	free_list(&in_tree, &tokens);
	return (1);
}
