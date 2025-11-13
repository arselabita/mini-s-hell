/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:32:07 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/15 15:07:53 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char const *set, char const c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;
	size_t	len;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_check(set, s1[start]) != 0)
		start++;
	end = ft_strlen(s1);
	if (end == 0)
		return (ft_calloc(1, sizeof(char)));
	while (ft_check(set, s1[end - 1]))
		end--;
	if (start > end)
		return (ft_calloc(1, sizeof(char)));
	len = end - start;
	return (ft_substr(s1, start, len));
}
//							FT_CHECK replace with ft_strchr
/* int	main(void)
{
	char str[] = "     HELLO     ";
	char set[] = "*";
	char *trim;

	printf("%s\n", str);
	printf("Trimm: %s\n", set);

	trim = (char *)ft_strtrim(str, set);
	printf("%s\n", trim);
	free(trim);
} */
