/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:34:54 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:34:55 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	size_src;

	size_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	dst = &dst[size_dst];
	if (size < size_dst)
		return (size_src + size);
	else if (size == 0)
		return (size_src + size_dst);
	else
	{
		while (*(src) && size-- - 1 > size_dst)
			*dst++ = *src++;
	}
	*(dst) = '\0';
	return (size_src + size_dst);
}
