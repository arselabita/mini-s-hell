/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:45 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/14 03:21:01 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints env struct with envp values
void	print_env(t_data *data)
{
	int	i;

	i = 0;
	printf("\nENV:\n\n");
	while (data->env[i])
		printf("%s\n", data->env[i++]);
	if (data->path_list)
	{
		i = 0;
		printf("\nPATH:\n");
		while (data->path_list[i])
			printf("%s\n", data->path_list[i++]);
	}
}
