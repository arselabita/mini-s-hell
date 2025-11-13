/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:24:40 by pjelinek          #+#    #+#             */
/*   Updated: 2025/08/14 18:35:13 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	zahl;

	zahl = n;
	if (zahl < 0)
	{
		ft_putchar_fd('-', fd);
		zahl *= -1;
	}
	if (zahl >= 0 && zahl <= 9)
	{
		ft_putchar_fd(zahl + '0', fd);
	}
	if (zahl > 9)
	{
		ft_putnbr_fd(zahl / 10, fd);
		ft_putnbr_fd(zahl % 10, fd);
	}
}
/*
int	main(void)
{
	long int zahl = -2147483648;
	int fd = 1;
	ft_putnbr_fd(zahl, fd);
} */
