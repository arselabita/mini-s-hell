/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:06:18 by netrunner         #+#    #+#             */
/*   Updated: 2025/11/13 21:13:11 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_exit_status = 0;

//handles ctrl + C
void	handler(int sig)
{
	g_exit_status = sig;
	if (VERBOSE)
		printf("\nVERBOSE: Exit Code: %i", g_exit_status + 128);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// signal struct for Ctrl +C , etc...
void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL); // NOT WORKING YET CTRL + BACKSLASH

	//sigaddset(SIGQUIT, &sa);
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
	memset(&data, 0, sizeof(t_data));
	prompt = "\001\033[1;32m\002❯ \001\033[1;37m\002minishell\001\033[0m\002 ▸ $ ";
	if (!init_env(envp, &data))
		return (cleanup(&data), 0);
	while (1)
	{
		init_signals();
		line = readline(prompt);
		if (!line) // NULL → Ctrl+D pressed (EOF)
			return (printf("exit\n"), cleanup(&data), 0);
		if (*line) // not empty input
		{
			if (*line != SPACE)
				add_history(line);
			//tokens = lexer(line);
			//ast = parser(tokens);
			//execute(ast);
			//free_all();
			printf("Input: %s\n", line);
		}
		free(line);
	}
	cleanup(&data);
	return (0);
}
