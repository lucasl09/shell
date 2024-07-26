/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:29:04 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:29:06 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	convert_to_hexa(char *result, unsigned long number)
{
	int				number_c;
	unsigned long	remainder;
	char			hex_number;
	char			tmp[20];
	int				start;

	number_c = -1;
	start = -1;
	if (utils(result, 'x', number))
		return (1);
	while (number_c++, number != 0)
	{
		remainder = number % 16;
		if (remainder < 10)
			hex_number = remainder + '0';
		else
			hex_number = 'a' + remainder - 10;
		*(tmp + number_c) = hex_number;
		number /= 16;
	}
	*(tmp + number_c) = '\0';
	while (++start, number_c)
		*(result + start) = *(tmp + number_c-- - 1);
	*(result + start) = '\0';
	return (start);
}

int	utils(char *str, char type, unsigned long number)
{
	if (type == 's')
	{
		if (!str)
			return (write(1, "(null)", 6));
	}
	else if (type == 'p')
	{
		if (!*str)
			return (write(1, "(nil)", 5));
	}
	else if (type == 'x' && number == 0)
	{
		*str = '0';
		*(str + 1) = '\0';
		return (1);
	}
	return (0);
}
