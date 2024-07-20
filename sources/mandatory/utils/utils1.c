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

int	ft_lstsize_token(t_token *head)
{
	int	count;

	count = 1;
	if (head == NULL)
		return (0);
	while (head->next != NULL)
	{
		head = head->next;
		count++;
	}
	return (count);
}

void	ft_unset(t_token *tokens)
{
	t_token	*current;

	current = tokens->next;
	if (current == NULL)
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	while (current != NULL)
	{
		if (current->content == NULL || ft_strlen(current->content) == 0)
			ft_printf("unset: %s: not a valid identifier\n", current->content);
		else if (unsetenv(current->content) != 0)
			perror("unsetenv");
		current = current->next;
	}
}

void	ft_valid_malloc(int *pipefds)
{
	if (!pipefds)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}
