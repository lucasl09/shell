/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:33:15 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:33:16 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_p;
	unsigned char		*dest_p;

	dest_p = (unsigned char *)dest;
	src_p = (const unsigned char *)src;
	if (dest < src)
	{
		while (n > 0)
		{
			*(dest_p) = *(src_p);
			dest_p++;
			src_p++;
			n--;
		}
		return (dest);
	}
	else if (dest > src)
	{
		while (n > 0)
		{
			*(dest_p + n - 1) = *(src_p + n - 1);
			n--;
		}
	}
	return (dest);
}
