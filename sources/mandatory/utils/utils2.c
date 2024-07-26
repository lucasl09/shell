/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:41:51 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/07/13 15:24:36 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				break ;
			j++;
		}
		if (!accept[j])
			return (i);
		i++;
	}
	return (i);
}

static int	parse_pipe(const char *input, int single_q, int double_q)
{
	int	index;
	int	valid;

	index = 0;
	valid = 0;
	while (input[index] != '\0')
	{
		if (input[index] == '\'')
			single_q++;
		else if (input[index] == '"')
			double_q++;
		if (input[index] == '|' && !(single_q % 2) && !(double_q % 2))
		{
			if (valid)
				return (0);
			valid = 1;
		}
		else if (ft_isspace(input[index]))
			valid = 0;
		else if (ft_isalnum(input[index]))
			valid = 0;
		index++;
	}
	return (valid);
}

int	check_pipe(const char *input)
{
	int	double_q;
	int	single_q;
	int	valid;

	double_q = 0;
	single_q = 0;
	valid = 0;
	if (input[0] == '|')
		return (0);
	valid = parse_pipe(input, single_q, double_q);
	if (valid)
		return (0);
	return (1);
}

char	*ft_strndup(const char *src, int size)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = size + 1;
	dest = ft_calloc(len, sizeof(char));
	if (!dest)
		return (NULL);
	while ((i + 1) < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}