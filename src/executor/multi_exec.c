/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:13:33 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/01 16:26:37 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_status(t_data *data, int pid)
{
	int	status;
	int exit_code;
	pid_t	wpid;

	exit_code = 0;
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				exit_code = 128 + WTERMSIG(status);
				if (VERBOSE)
				{
					if (WTERMSIG(status) == SIGSEGV)
						fprintf(stderr, "\033[31m[SIGSEGV]\033[0m\n");
					else if (WTERMSIG(status) == SIGBUS)
						fprintf(stderr, "\033[31m[SIGBUS]\033[0m\n");
					else if (WTERMSIG(status) == SIGABRT)
						fprintf(stderr, "\033[31m[SIGABRT]\033[0m\n");
					else if (WTERMSIG(status) == SIGFPE)
						fprintf(stderr, "\033[31m[SIGFPE]\033[0m\n");
					else if (WTERMSIG(status) == SIGPIPE)
						fprintf(stderr, "\033[31m[SIGPIPE]\033[0m\n");
					else if (WTERMSIG(status) == SIGILL)
						fprintf(stderr, "\033[31m[SIGILL]\033[0m\n");
				}
			}
		}
		wpid = wait(&status);
	}
	data->return_value = exit_code;
	if (VERBOSE)
		fprintf(stderr, "ExitCode: %i\n", data->return_value);
	//exit(exit_code);
}
void	ft_close(t_data *data)
{
	if (data->fd.prev[0] >= 0)
		close(data->fd.prev[0]);
	if (data->fd.prev[1] >= 0)
		close(data->fd.prev[1]);
	if (data->fd.curr[0] >= 0)
		close(data->fd.curr[0]);
	if (data->fd.curr[1] >= 0)
		close(data->fd.curr[1]);
	ft_memset(&data->fd, -1, sizeof(t_fds));
	return ;
}

static void	child_process(t_data *data, t_cmds *cmd, int loop)
{
	if (loop == 0) // 1ST Loop, redir pipe to stdout
	{
		if (dup2(data->fd.curr[1], STDOUT_FILENO) < 0)
			child_cleanup(1, "child[1] - dup2 fd.curr failed\n", data, cmd);
	}
	else if (loop > 0 && loop < data->list.size - 1)  // IN BETWEEN cmd 2 - (n-1)
	{
		if (dup2(data->fd.prev[0], STDIN_FILENO) < 0)
			child_cleanup(1, "child - dup2 fd.prev[0] failed\n", data, cmd);
		if (dup2(data->fd.curr[1], STDOUT_FILENO) < 0)
			child_cleanup(1, "child - dup2 fd.curr[1]] failed\n", data, cmd);
	}
	else if (loop == data->list.size - 1) // Last COMMAND
	{
		if (dup2(data->fd.prev[0], STDIN_FILENO) < 0)
			child_cleanup(1, "child[last] - dup2 fd.prev[0] failed\n", data, cmd);
	}
	ft_close(data);
	exec_cmd(data, cmd);
}


static void	parent_process(t_data *data, t_cmds *cmd, int loop)
{
	if (close(data->fd.prev[0]) < 0 || close(data->fd.prev[1]) < 0)
		child_cleanup(1, "parent - close fd.prev failed\n", data, cmd);
	if (loop != data->list.size - 1)
	{
		data->fd.prev[0] = data->fd.curr[0];
		data->fd.prev[1] = data->fd.curr[1];
	}
	ft_memset(&data->fd.curr, -1, sizeof(data->fd.curr));
}

void	multi_cmds(t_data *data, t_cmds *cmd)
{

	int		i;
	pid_t	pid;

	pid = 0;
	if (pipe(data->fd.prev) < 0)
		child_cleanup(1, "open pipe fd.prev failed\n", data, cmd);
	i = -1;
	while (i < data->list.size - 1)
	{
		i++;
		//init_signals(); /// RIGHT POS HERE ???
		if (i != data->list.size - 1)
			if (pipe(data->fd.curr) < 0)
				child_cleanup(1, "pipe fd.curr failed\n", data, cmd);
		pid = fork();
		if (pid < 0)
			child_cleanup(1, "error fork\n", data, cmd);
		if (pid == 0)
			child_process(data, cmd, i);
		else
			parent_process(data, cmd, i);
		cmd = cmd->next;
	}
	get_exit_status(data, pid);
	return ;
}
