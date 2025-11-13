/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:36:44 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/09 12:33:45 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p;
	size_t			total;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb > (size_t)SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	return (ft_bzero(p, total));
}

/* int	main(void)
{
	char elements[10];
	printf("elemnts: %zu\n", sizeof(elements));
	//printf("elemnts: %zu\n", elements);

	char *p = ft_calloc(10, sizeof(elements[0]));

	size_t i = 0;
	while (i < 10)
	{
		printf("elements[%zu]: %d\n", i, p[i]);
		i++;
	}
	free(p);
} */
