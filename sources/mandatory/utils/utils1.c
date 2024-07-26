/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:34:32 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/07/14 16:41:44 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

char	*ft_strspn_end(char *str, const char *delim)
{
	while (*str && strchr(delim, *str))
		str++;
	return (str);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*ret;

	if (str)
		last = str;
	if (!last || !*last)
		return (NULL);
	last = ft_strspn_end(last, delim);
	if (!*last)
		return (NULL);
	ret = last;
	while (*last && !strchr(delim, *last))
		last++;
	if (*last)
	{
		*last = '\0';
		last++;
	}
	else
		last = NULL;
	return (ret);
}

t_token	*initialize_rdt(int *i, char *cmd_line)
{
	char	c;

	if (cmd_line[*i] == '<' || cmd_line[*i] == '>')
	{
		c = cmd_line[*i];
		if (cmd_line[(*i) + 1] == c && cmd_line[(*i) + 2] == c)
		{
			ft_putstr_fd("Syntax error near unexpected token \'", 1);
			ft_putchar_fd(c, 1);
			ft_putendl_fd("\'", 1);
			return (NULL);
		}
		return (for_tredirect(i, cmd_line, c));
	}
	return (NULL);
}
