/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:32:19 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:32:21 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atoi(const char *nptr)
{
	int			signal;
	long int	sun;

	sun = 0;
	signal = 1;
	while ((*(nptr) >= 9 && *(nptr) <= 13) || *(nptr) == 32)
		nptr++;
	if (*(nptr) == '+' || *(nptr) == '-')
	{
		if (*(nptr) == '-')
			signal *= -1;
		nptr++;
		if (*(nptr) < 48 && *(nptr) > 57)
			return (0);
	}
	while (*(nptr) >= 48 && *(nptr) <= 57)
	{
		sun = (sun * 10) + *(nptr) - 48;
		nptr++;
	}
	return (sun * signal);
}
