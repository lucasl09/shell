/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:34:26 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:34:27 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_last;
	char	character;
	int		finded;

	finded = 0;
	character = (unsigned char)c;
	s_last = (char *)s;
	while (*(s))
	{
		if (*(s) == character)
		{
			s_last = (char *)s;
			finded = 1;
		}
		s++;
	}
	if (*(s) == character)
		return ((char *)s);
	if (finded == 1)
	{
		return (s_last);
	}
	return (NULL);
}
