/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:27:55 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:27:58 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	index;
	size_t	sub_index;
	char	*str;

	if (!s1)
	{
		s1 = allocate_char(1);
		*s1 = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = allocate_char(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	index = -1;
	sub_index = 0;
	if (s1)
		while (*(s1 + ++index) != '\0')
			*(str + index) = *(s1 + index);
	while (*(s2 + sub_index) != '\0')
		*(str + index++) = *(s2 + sub_index++);
	*(str + ft_strlen(s1) + ft_strlen(s2)) = '\0';
	free(s1);
	return (str);
}

char	*allocate_char(size_t size)
{
	char	*str;

	str = (char *)malloc(size * sizeof(char));
	if (str == NULL)
	{
		free(str);
		return (NULL);
	}
	return (str);
}
