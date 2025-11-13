/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:37:18 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/03 11:52:49 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int str)
{
	if ((ft_isalpha(str) || ft_isdigit(str)))
		return (1);
	return (0);
}

/* int	main(void)
{
	int	a = 65;
	int	b = '&';
	int	c = '5';

	printf("%d\n", ft_isalnum(a));
	printf("%d\n", ft_isalnum(b));
	printf("%d", ft_isalnum(c));
} */
