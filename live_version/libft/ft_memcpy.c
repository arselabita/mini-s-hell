/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:38:28 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/15 13:44:25 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst;
	unsigned char		*source;

	dst = (unsigned char *) dest;
	source = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return ((void *)dest);
}

/* int	main(void)
{
	char *p;
	char str[20];
	char src[] = "Hi,welcome!";

	p = ft_memcpy(str, src, 2);


	printf("%s\n", p);
	p = memcpy(str, src, 2);
	printf("%s", p);

} */
