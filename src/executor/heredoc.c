/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 02:34:22 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/01 05:03:37 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_into_heredoc(t_redirs *redirs, int fd)
{
	char *line;
	char *delimiter;
	int delimiter_len;

	delimiter = redirs->filename;
	delimiter_len = ft_strlen(delimiter);
	init_signals_heredoc();
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if ((!line) || !ft_strncmp(line, delimiter, delimiter_len)
			|| g_signal == 1)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
}

static char	*get_filename(int index)
{
	int pid_nb;
	char *tmp;
	char *nb;
	char *pid;
	char *filename;

	pid_nb = getpid();
	pid = ft_itoa(pid_nb);
	if (!pid)
		return (NULL);
	nb = ft_itoa(index);
	if (!nb)
		return (free(pid), NULL);
	tmp = ft_strjoin(pid, nb);
	free(pid);
	free(nb);
	if (!tmp)
		return(NULL);
	filename = ft_strjoin("heredoc_", tmp);
	free(tmp);
	if (!filename)
		return (NULL);
	return (filename);
}

// creates a file with random name from name + pid + index
static void	create_file(t_data *data, t_redirs *redir)
{
	int fd;
	char *heredoc_name;
	int index;

	fd = -1;
	if (!redir)
		return ;
	index = data->heredoc.index;
	printf("Creating heredoc index number: %d\n", index);
	heredoc_name = get_filename(index);
	data->heredoc.files[index] = ft_strdup(heredoc_name);
	fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || !heredoc_name || !data->heredoc.files[index])
		cleanup(data, ERROR);
	write_into_heredoc(redir, fd);
	free(redir->filename);
	redir->filename = NULL;
	redir->typ = REDIR_IN;
	redir->filename = heredoc_name;
	data->heredoc.index++;
	if (fd >= 0)
		close(fd);
	if (VERBOSE)
		fprintf(stderr, "Created heredoc file: %s\n", redir->filename);

}

// finds heredocs by heredoc flag if true!
int	heredocs(t_data *data, t_cmds *cmd)
{
	t_cmds		*curr;
	t_redirs	*redirs;

	curr = cmd;
	data->heredoc.files = ft_calloc(data->heredoc.count + 1, sizeof(char *));
	if (!data->heredoc.files)
		cleanup(data, ERROR);
	while (curr)
	{
		redirs = curr->redirs;
		while (redirs)
		{
			if (redirs->heredoc == true)
				create_file(data, redirs);
			redirs = redirs->next;
		}
		curr = curr->next;
	}
	init_signals_prompt();
	if (g_signal == 1)
	{
		fprintf(stderr, "signal_check (heredocs)\n");
		cleanup(data, RESET);
		return (SIGINT);
	}
	return (0);
}
