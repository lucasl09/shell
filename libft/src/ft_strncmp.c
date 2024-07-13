/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:34:35 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:34:37 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	n--;
	while (*(s1) && *(s2) && *(s1) == *(s2) && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*(s1) - (unsigned char)*(s2));
}
