/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:33:27 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/04 13:53:05 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	unsigned char	d;

	d = (char) c;
	if (d >= 'A' && d <= 'Z')
		return (c + 32);
	return (c);
}

/* int	main(void)
{
	char	a = 'A';
	int		b = -5;

	printf("%c\n", ft_tolower(a));
	printf("%d\n", ft_tolower(b));
} */
