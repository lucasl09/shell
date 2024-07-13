/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:34:02 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:34:03 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	character;

	character = (unsigned char)c;
	str = (char *)s;
	while (*(str))
	{
		if (*(str) == character)
			return ((char *)str);
		str++;
	}
	if (*(str) == character)
		return ((char *)str);
	return (NULL);
}
