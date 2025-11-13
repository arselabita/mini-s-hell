/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:28:24 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/04 17:22:17 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	letter;
	size_t			i;

	str = (unsigned char *)s;
	letter = (unsigned char) c;
	i = 0;
	if (str == NULL)
		return (NULL);
	while (i < n)
	{
		if (str[i] == letter)
			return ((unsigned char *) str + i);
		i++;
	}
	return (NULL);
}

// n > len -> undefined behaviour
