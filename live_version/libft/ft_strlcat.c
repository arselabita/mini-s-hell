/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:44:01 by pielinek          #+#    #+#             */
/*   Updated: 2025/05/04 19:46:15 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;

	dest_len = 0;
	while (dest_len < size && dst[dest_len])
		dest_len++;
	if (size == dest_len)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && dest_len + i + 1 < size)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + ft_strlen(src));
}

/* int	main(void)
{
	char *dst;
	char src[] = "lorem";

	dst = (char *)malloc(sizeof(*dst) * 15);

	size_t result = ft_strlcat(dst, src, 6);
	printf("%s\n", dst);
	printf("Komplette Stringlänge ohne \\0: %zu\n", result);
} */
