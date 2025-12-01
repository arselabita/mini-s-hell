/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:42:02 by netrunner         #+#    #+#             */
/*   Updated: 2025/12/01 00:20:03 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_relative_path(t_data *data, t_cmds *cmd)
{
	int	error_code;

	error_code = 0;
	if (access(cmd->argv[0], X_OK) == -1)
	{
		error_code = errno;
		handle_errno(data, cmd, error_code);
	}
	if (execve(cmd->argv[0], cmd->argv, data->env) == -1)
	{
		error_code = errno;
		handle_errno(data, cmd, error_code);
	}
	child_cleanup(127, ": command not found\n", data, cmd);
}


void	apply_execve(t_data *data, t_cmds *cmd)
{
	int	error_code;

	error_code = 0;
	if (access(data->exec.path, X_OK) == 0)
	{
		execve(data->exec.path, cmd->argv, data->env);
		error_code = errno;
		free(data->exec.path);

		handle_errno(data, cmd, error_code);
	}
}

static char	*create_path(char *dir, char *cmd_line, t_data *data, t_cmds *cmd)
{
	char	*tmp;
	char	*full_path;

	if (!cmd_line || !cmd_line[0])
		child_cleanup(127, " \"\" : empty command not valid\n", data, cmd);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd_line);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

void	exec_cmd(t_data *data, t_cmds *cmd)
{
	int		i;

	i = 0;
	if (!!cmd->redirs) // if redirs type is NULL dont go in
		handle_redirections(data, cmd);
	if (ft_strchr(cmd->argv[0], '/') || (cmd->argv[0][0] == '.'
		&& cmd->argv[0][1] == '/' ) || !data->path_list || !data->path_list[0])
		execute_relative_path(data, cmd);
	while (data->path_list[i])
	{
		data->exec.path = create_path(data->path_list[i], cmd->argv[0], data, cmd);
		if (!data->exec.path)
			child_cleanup(1, " : create_exec_path failed\n", data, cmd);
		apply_execve(data, cmd);
		free(data->exec.path);
		i++;
	}
	child_cleanup(127, ": command not found\n", data, cmd);/////
}

void	single_cmd(t_data *data, t_cmds *cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return ; // error message, exit code
	if (pid == 0)
		exec_cmd(data, cmd);
	else
		get_exit_status(data, pid);


	/*
	//relative path or absolut path ??
		-> exec direct path!
	// check binary
		-> exec ./a.out
	// create execution path
		strjoin paths and send to execve
	*/




}
