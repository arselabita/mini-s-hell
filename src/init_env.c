	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:45 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/27 22:44:52 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*increment_shlvl(char *str)
{
	char	*level;
	char	*shlvl;
	int		num;

	shlvl = NULL;
	level = ft_extract_digits(str);
	if (!level)
		return (NULL);
	num = ft_atoi(level);
	free(level);
	level = ft_itoa(num + 1);
	if (!level)
		return (NULL);
	shlvl = ft_strjoin("SHLVL=", level);
	if (!shlvl)
		return (free(level), NULL);
	free(level);
	if (VERBOSE)
		fprintf(stderr, "SHLVL\n\n%s\n", shlvl);
	return (shlvl);
}

// add SHLVL, PWD, _= to environment if they have been removed by command env -u SHLVL
static bool	add_env(t_data *data, int i)
{
	char *str;

	if (!data->flag.shlvl)
	{
		data->env[i] = ft_strdup("SHLVL=1");
		if (!data->env[i])
			return (false);
		i++;
	}
	if (!data->flag.pwd)
	{
		str = getcwd(NULL, 0);
		data->env[i] = ft_strjoin("PWD=", str);
		if (!data->env[i])
			return (free(str), false);
		i++;
	}
	if (!data->flag.last_cmd)
	{
		data->env[i] = ft_strdup("_=/usr/bin/env");
		if (!data->env[i])
			return (false);
	}
	return (true);
}

//counts envp for allocation and checks if SHLVL, PWD, and _= existis and if not it counts i for later allocation!
int	loop_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			data->flag.shlvl = true;
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			data->flag.pwd = true;
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			data->flag.last_cmd = true;
		i++;
	}
	if (!data->flag.shlvl)
		i++;
	if (!data->flag.pwd)
		i++;
	if (!data->flag.last_cmd)
		i++;
	return (i);
}
//copies enviroment from envp to data->env[i]
static bool	extract_env(t_data *data, char **envp)
{
	int	i;

	i = loop_envp(data, envp);
	data->env = ft_calloc(i + 1, sizeof(char *));
	if (!data->env)
		return (false);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			data->env[i] = increment_shlvl(envp[i]);
		else if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			data->env[i] = ft_strdup(envp[i]);
			data->path_list = ft_split(&envp[i][5], ':');
			if (!data->path_list)
				return (false);
		}
		else
			data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			return (false);
		i++;
	}
	if (!add_env(data, i))
		return (false);
	return (true);
}

//creates environment if envp is empty
static bool	create_env(t_data *data)
{
	char	**env;
	char	*str;


	env = NULL;
	data->env = ft_calloc(4, sizeof(char *));
	if (!data->env)
		return (false);
	env = data->env;
	str = getcwd(NULL, 0);
	if (!str)
		return (false);
	env[PWD] = ft_strjoin("PWD=", str);
	free(str);
	if (!env[PWD])
		return (false);
	env[SHLVL] = ft_strdup("SHLVL=1");
	if (!env[SHLVL])
		return (false);
	env[LAST_CMD] = ft_strdup("_=/usr/bin/env");
	if (!env[LAST_CMD])
		return (false);
	return (true);
}

//fills selfmade data->env struct with envp values
bool	init_env(char **envp, t_data *data)
{
	if (!envp || !*envp)
	{
		if (!create_env(data))
			return (false);
	}
	else
	{
		if (!extract_env(data, envp))
			return (false);
	}
	if (VERBOSE)
		print_env(data);
	return (true);
}
