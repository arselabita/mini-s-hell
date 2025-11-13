/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:21:16 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/04 10:20:45 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*arr;

	arr = s;
	if (!s)
		return (NULL);
	i = 0;
	while (i < n)
	{
		arr[i] = (unsigned char) c;
		i++;
	}
	return ((void *)s);
}
/*
int	main(void)
{
    char arr[10];
	char *p = ft_memset(arr, '0', 10);

	int i = 0;
	while(i < 10)
	{
		printf("int:%d vs char: %c\n", p[i], p[i]);
		i++;
	}
}*/
