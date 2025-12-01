/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2025/12/01 05:08:55 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

int	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	ft_memset(&data->fd, -1, sizeof(t_fds));
	return (1);
}

//main
int	main(int ac, char **av, char **envp)
{
	char	*prompt;
	char	*line;
	t_data	data;

	(void) av;
	if (ac != 1)
		return (0);

	prompt = "\001\033[1;32m\002❯ \001\033[1;37m\002minishell\001\033[0m\002 ▸ $ ";
	if (!!init_signals_prompt() || !init_data(&data) || !init_env(envp, &data))
		cleanup(&data, 1);

	//// looop version
	while (1)
	{
		line = readline(prompt);
		if (!line) // NULL → Ctrl+D pressed (EOF)
			return (fprintf(stderr, "exit\n"), cleanup(&data, OK_EXIT), 0);
		if (*line) // not empty input
		{
			if (*line != SPACE)
				add_history(line);

			//tokens = lexer(line);
			//cmd = parser(tokens);
			debug_build_commands(&data);
			print_cmd_list(data.list.head);

			fprintf(stderr, "data_list_size: %i\n", data.list.size);

			if (heredocs(&data, data.list.head) == SIGINT)
			{
				free(line);
				continue ;
			}
			//expansions

			executor(data.list.head, &data);
			cleanup(&data, RESET);
		}
		free(line);
	}
	return (0);
}
