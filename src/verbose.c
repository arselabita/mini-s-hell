/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:45 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/01 04:45:54 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints env struct with envp values
void	print_env(t_data *data)
{
	int	i;

	i = 0;
	fprintf(stderr, "\nDATA_ENV:\n\n");
	while (data->env[i])
		fprintf(stderr, "%s\n", data->env[i++]);
	if (data->path_list)
	{
		i = 0;
		fprintf(stderr, "\nPATH_LIST:\n");
		while (data->path_list[i])
			fprintf(stderr, "%s\n", data->path_list[i++]);
	}
}
