/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:32:34 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:32:36 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isalnum(int c)
{
	char	c_cast;

	c_cast = (char)c;
	if (ft_isalpha(c_cast) || ft_isdigit(c_cast))
		return (1);
	else
		return (0);
}
