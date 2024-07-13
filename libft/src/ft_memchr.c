/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:33:01 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:33:03 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_cast;
	unsigned char	c_cast;

	s_cast = (unsigned char *)s;
	c_cast = (unsigned char)c;
	while (n > 0)
	{
		if (*s_cast == c_cast)
			return ((void *)s_cast);
		s_cast++;
		n--;
	}
	return (NULL);
}
