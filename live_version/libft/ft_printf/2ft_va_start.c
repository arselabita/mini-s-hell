/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2ft_va_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:43:03 by pjelinek          #+#    #+#             */
/*   Updated: 2025/08/14 18:54:18 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*find_specifier(const char *str, int c)
{
	unsigned char	letter;

	letter = (unsigned char) c;
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == letter)
			return ((char *)str);
		str++;
	}
	if (letter == '\0')
		return ((char *)str);
	return (NULL);
}

int	ft_va_start(const char *str, va_list ap)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == '%')
		{
			if (find_specifier("cspdiuxX%", str[i + 1]) && str[i + 1])
				count += find_arg(str[i + 1], ap);
			else
				return (-1);
			i += 2;
		}
		if (str[i] && write(1, &str[i], 1))
		{
			i++;
			count += 1;
		}
	}
	return (count);
}
