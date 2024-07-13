/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:34:29 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:34:31 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	len_sub;
	int		result;

	result = 0;
	index = 0;
	len_sub = ft_strlen(little);
	if (len_sub == 0)
		return ((char *)big);
	while (*big && len >= len_sub)
	{
		result = ft_strncmp(big, little, len_sub);
		if (result == 0)
			return ((char *)big + index);
		big++;
		len--;
	}
	return (NULL);
}
