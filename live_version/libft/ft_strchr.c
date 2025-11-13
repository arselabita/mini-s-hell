/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:30:05 by pjelinek          #+#    #+#             */
/*   Updated: 2025/05/04 14:48:50 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	letter;

	letter = (unsigned char) c;
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == letter)
			return ((char *)str);
		str++;
	}
	if (letter == '\0')
		return ((char *)str);
	return (NULL);
}

/* int main(void)
{
    char str[] = "ort das ich suche";
    char suche = '\0';

    char *p = ft_strchr(str, suche);
    if (p != NULL)
    {
        printf("Gefunden: '%c'\n", *p);               → s
        printf("Ab hier: \"%s\"\n", p);               → s wort das ich suche
        printf("Index im String: %ld\n", p - str);  2 (weil p zeigt auf str[2])
    }
    else
        printf("Nicht gefunden.\n");
}*/
