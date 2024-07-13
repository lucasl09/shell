/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:33:11 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:33:13 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_p;
	const char	*src_p;

	if (dest == src)
		return (dest);
	dest_p = (char *)dest;
	src_p = (const char *)src;
	while (n-- > 0)
		*dest_p++ = *src_p++;
	return (dest);
}
