/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:20:52 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/15 14:45:53 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*source;
	size_t			i;

	dst = (unsigned char *) dest;
	source = (unsigned char *) src;
	i = 0;
	if (!dst || !source)
		return (NULL);
	if (dst == source || n == 0)
		return ((void *)dest);
	if (dst < source)
	{
		while (i < n)
		{
			dst[i] = source[i];
			i++;
		}
	}
	else
		while (n--)
			dst[n] = source[n];
	return ((void *)dest);
}

/* int	main(void)
{
	char array[] = "ABCDEFGHIJKLMNO";
	char arr[] = "ABCDEFGHIJKLMNO";

	char *p = ft_memmove(&arr[8], &arr[3], 5);
	printf("%s\n\n", p);
	char *s = memmove(&array[8], &array[3], 5);
	printf("%s\n\n", s);
} */
