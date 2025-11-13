/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:45 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/13 13:56:14 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fills selfmade env struct with envp values
void	update_env(char **envp, t_data *data)
{
	int i;
	
	i = 0;
	if (!envp)
	{
		printf("envp empty");
		return ;
	}
	if (!*envp && !data->env)
	{
		data->env = ft_calloc(4, sizeof(char *));
		if (!data->env)
			return ;
		data->env[PWD] = ft_strjoin("PWD=", "HIIIII");
		data->env[SHLVL] = ft_strdup("SHLVL=1");
		data->env[EXEC] = ft_strdup("_=/minishell");
		if (VERBOSE)
		{
			printf("VERBOSE:\tenv[PWD]: %s\n", data->env[PWD]);
			printf("VERBOSE:\tenv[SHLVL]: %s\n", data->env[SHLVL]);
			printf("VERBOSE:\tenv[EXEC]: %s\n", data->env[EXEC]);
		}
	}
	else
	{
		if (data->env)
		{
			free_split(data->env);
			data->env = NULL;
		}	
		while (envp[i++])
			;
		if (!data->env)
			data->env = ft_calloc(i + 1, sizeof(char *));
		if (!data->env)
			return ;
		i = 0;
		while (envp[i])
		{
			if (ft_strncmp(envp[i], "SHLVL=", 6))
			{
				data->env[i] = ft_strdup(envp[i]); // CHANGE FUNCTION, JUST FOR VALGRIND THERE ATM
			}
			else
				data->env[i] = ft_strdup(envp[i]);
			i++;
		}
	} 
	if (VERBOSE)
	{
		i = 0;
		while (data->env[i])
			printf("%s\n", data->env[i++]);
	}
	return ;
}
