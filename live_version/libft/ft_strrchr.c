/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:31:56 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/04 18:32:45 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	letter;
	char			*last;
	char			*tmp;
	size_t			i;

	tmp = (char *) str;
	letter = (unsigned char) c;
	last = NULL;
	i = 0;
	if (tmp == NULL)
		return (NULL);
	if (letter == '\0')
		return (tmp + (ft_strlen(tmp)));
	while (tmp[i])
	{
		if (tmp[i] == letter)
			last = tmp + i;
		if (tmp[i + 1] == '\0')
			return (last);
		i++;
	}
	return (NULL);
}

/* int main(void)
{
    char str[] = "bonjour";
    char suche = 's';

    char *p = ft_strrchr(str, suche);
    if (p != NULL)
    {
        printf("Gefunden: '%c'\n", *p);
        printf("Ab hier: \"%s\"\n", p);
		printf("Index im String: %ld\n", p - str);
    }
    else
        printf("Nicht gefunden.\n");
} */
