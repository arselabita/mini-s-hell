/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:39:35 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/22 02:41:29 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	i = 0, bytes= 0;
	char	*line;
	int	j = 0;

	if (fd < 0 || BUFFER_SIZE <= 0 || !(line = calloc(10000, 1)))
		return (NULL);
	while (1)
	{
		if (i >= bytes)
		{
			i = 0;
			bytes= read(fd, buf, BUFFER_SIZE);
			if (bytes <= 0)
			{
				if (bytes < 0)
					return (free(line), perror("Error"), NULL);
				break ;
			}
		}
		line[j++] = buf[i++];
		if (line[j - 1] == '\n')
			break ;
	}
	if (j)
	{
		line[j] = '\0';
		return (line);
	}
	else
	{
		free(line);
		line = NULL;
		i = 0;
		bytes = 0;
		return (NULL);
	}
}
