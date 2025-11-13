/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3find_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:53:12 by pjelinek          #+#    #+#             */
/*   Updated: 2025/08/29 12:56:44 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_arg(char c, va_list ap)
{
	if (c == 'c')
		return (write(1, (char []){va_arg(ap, int)}, 1));
	if (c == 's')
		return (ft_arg_string(va_arg(ap, char *)));
	if (c == 'd' || c == 'i')
		return (ft_int_check(va_arg(ap, int)));
	if (c == 'u')
		return (ft_putnbr_base(va_arg(ap, unsigned int), 10, 'z'));
	if (c == 'p')
		return (ft_arg_pointer(va_arg(ap, void *), c));
	if (c == 'x' || c == 'X')
		return (ft_putnbr_base(va_arg(ap, unsigned int), 16, c));
	if (c == '%')
		return (write(1, &c, 1));
	return (0);
}
