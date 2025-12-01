/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:38:45 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/01 04:23:12 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_cleanup(int exit_code, char *message, t_data *data, t_cmds *cmd)
{
	ft_close(data);
	if (!message)
	{
		if (data->flag.redirect_fail == false)
			perror(cmd->argv[0]);
	}
	else
	{
		if (cmd->argv)
			write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, message, ft_strlen(message));
	}
	data->return_value = exit_code;
	data->flag.redirect_fail= false;
	cleanup(data, exit_code);
}

void	handle_errno(t_data *data, t_cmds *cmd, int error_code)
{
	if (error_code == 13 && cmd->argv[0][0] == '/')
		child_cleanup(126, " : Is a directory\n", data, cmd);
	else if (error_code == ENOENT)
		child_cleanup(127, NULL, data, cmd);
	else if (error_code == ENOTDIR || error_code == EISDIR
		|| error_code == ENOEXEC || error_code == EACCES
		|| error_code == ELOOP || error_code == ETXTBSY
		|| error_code == ENAMETOOLONG || error_code == EINVAL)
		child_cleanup(126, NULL, data, cmd);
	else if (/* error_code == ENOMEN ||  */error_code == EMFILE
		|| error_code == ENFILE || error_code == E2BIG
		|| error_code == EFAULT)
		child_cleanup(1, NULL, data, cmd);
}


