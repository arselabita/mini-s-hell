/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:45:29 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/03 11:52:55 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int str)
{
	if (str >= 32 && str < 127)
		return (1);
	return (0);
}

/* int	main(void)
{
	int a = '6';
	int b = 126;

	printf("%d\n", ft_isprint(a));
	printf("%d", ft_isprint(b));
} */
