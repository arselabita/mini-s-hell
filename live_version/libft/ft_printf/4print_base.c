/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4print_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:53:12 by pjelinek          #+#    #+#             */
/*   Updated: 2025/08/29 12:56:50 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_countbase(size_t n, size_t basedivider)
{
	int			digits;
	long int	num;

	num = n;
	digits = 0;
	if (num == 0)
		digits = 1;
	while (num > 0)
	{
		num = num / basedivider;
		digits++;
	}
	return (digits);
}

int	ft_putnbr_base(size_t hexanum, size_t divider, char Xx)
{
	char	*base;
	int		count;

	count = ft_countbase(hexanum, divider);
	if (Xx == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (hexanum >= divider)
	{
		ft_putnbr_base((hexanum / divider), divider, Xx);
		write(1, &base[hexanum % divider], 1);
	}
	if (hexanum < divider)
		write(1, &base[hexanum % divider], 1);
	return (count);
}

int	ft_arg_pointer(void *p, char c)
{
	size_t	hexanum;

	if (!p)
		return (write(1, "(nil)", 5));
	else
	{
		hexanum = (size_t) p;
		return (write(1, "0x", 2) + ft_putnbr_base(hexanum, 16, c));
	}
	return (0);
}

int	ft_int_check(int nb)
{
	if (nb < 0)
		return (write(1, "-", 1) + ft_putnbr_base((unsigned int) -nb, 10, 'n'));
	else
		return (ft_putnbr_base(nb, 10, 'n'));
}
