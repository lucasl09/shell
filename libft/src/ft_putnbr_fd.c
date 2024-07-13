/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:33:39 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:33:42 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	n_l;

	n_l = n;
	if (n_l < 0)
	{
		ft_putchar_fd('-', fd);
		n_l = n_l * -1;
	}
	if (n_l >= 10)
		ft_putnbr_fd(n_l / 10, fd);
	ft_putchar_fd((n_l % 10) + '0', fd);
}
