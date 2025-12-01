/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:49:20 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/01 16:47:57 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	redirs_lstclear(t_redirs **lst)
{
	t_redirs	*redirs;
	t_redirs	*next;

	if (!lst || !*lst)
		return ;
	redirs = *lst;
	while (redirs)
	{
		next = redirs->next;
		free(redirs->filename);
		free(redirs);
		redirs = next;
	}
	*lst = NULL;
}

void	cmd_lstclear(t_cmds **lst)
{
	t_cmds	*cmd;
	t_cmds	*next;

	if (!lst || !*lst)
		return;
	cmd = *lst;
	while (cmd)
	{
		next = cmd->next;
		free_split(cmd->argv);
		redirs_lstclear(&cmd->redirs);
		free(cmd);
		cmd = next;
	}
	*lst = NULL;
}

void	cleanup(t_data *data, int exit_code)
{
	t_cmds *cmd = data->cmd;
	if (data->env && exit_code != RESET)
	{
		free_split(data->env);
		data->env = NULL;
	}
	if (data->path_list && exit_code != RESET)
	{
		free_split(data->path_list);
		data->path_list = NULL;
	}
	if (cmd)
	{
		cmd_lstclear(&cmd);
		ft_memset(&data->cmd, 0, sizeof(t_cmds));
	}
	if (data->heredoc.files)
	{
		int i = 0;
		while (i < data->heredoc.count)
		{
			unlink(data->heredoc.files[i++]);
			fprintf(stderr, "HEREDOC FILE %s DELETED\n", data->heredoc.files[i - 1]);
		}
		free_split(data->heredoc.files);
		ft_memset(&data->heredoc, 0, sizeof(t_heredoc));

	}
	ft_memset(&data->fd, -1, sizeof(t_fds));
	ft_memset(&data->list, 0, sizeof(t_list));
	if (exit_code == RESET)
		return ;
	exit(exit_code); ///// fuer debbuging
}
