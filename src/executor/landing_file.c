/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   landing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:12:31 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/27 16:15:02 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	built_in_execution(t_data *data)
// {
// 	if (VERBOSE)
// 		printf("BUILT_IN %s = TRUE\n", data->cmd.argv[0]);
// 	return ;
// }

/* static bool	built_in(char **argv)
{
	if (!argv[CMD] || !*argv[CMD])
		return (false);
	if (ft_strncmp("echo", argv[CMD], 4) == 0)
		return (true);
	else if (ft_strncmp("cd", argv[CMD], 2) == 0)
		return (true);
	else if (ft_strncmp("exit", argv[CMD], 4) == 0)
		return (true);
	else if (ft_strncmp("env", argv[CMD], 3) == 0)
		return (true);
	else if (ft_strncmp("pwd", argv[CMD], 3) == 0)
		return (true);
	else if (ft_strncmp("unset", argv[CMD], 5) == 0)
		return (true);
	else if (ft_strncmp("export", argv[CMD], 6) == 0)
		return (true);
	return (false);
} */




void	executor(t_cmds *cmd, t_data *data)
// void	executor(char *line, t_data *data)
{

	/* 	if (data->list.size == 1 && builtin(data->cmd.argv))
		built_in_execution(data); */
	if (data->list.size == 1)
		single_cmd(data, cmd);
	else
		multi_cmds(data, cmd);
}
