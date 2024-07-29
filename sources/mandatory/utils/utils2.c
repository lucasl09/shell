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
