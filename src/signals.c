/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:32:40 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/01 04:17:30 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handles ctrl + C in heredoc
void	heredoc_handler(int sig)
{
	(void) sig;
	if (VERBOSE)
		write(1, "\n(CTRL + C) Heredoc Exit: 130", 30);
	write(1, "\n", 1);
	g_signal = 1;
}

// signal struct for Ctrl +C ,in heredoc.
void	init_signals_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

//handles ctrl + C in readline
void	prompt_handler(int sig)
{
	(void) sig;
	if (VERBOSE)
		write(1, "\n(CTRL + C) Exit Code: 130", 27);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = 0;
}

// signal struct for Ctrl +C , etc...
void	*init_signals_prompt(void)
{
	struct sigaction	sa;

	sa.sa_handler = prompt_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (NULL);
}
