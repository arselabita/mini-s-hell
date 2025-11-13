/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:33:59 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/04 13:53:49 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	unsigned char	d;

	d = (unsigned char) c;
	if (d >= 'a' && d <= 'z')
		return (c - 32);
	return (c);
}

/* int	main(void)
{
	char a = 'a';
	int b = 5;

	printf("%c\n", ft_toupper(a)); // A
	printf("%c\n", ft_toupper(b)); // B
} */
