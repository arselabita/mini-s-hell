/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2025/11/14 02:55:10 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _DEFAULT_SOURCE

# ifndef VERBOSE
#  define VERBOSE 0
# endif

# define PWD 0
# define SHLVL 1
# define LAST_CMD 2
# define USER 3
# define HOME 4

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct s_flag
{
	bool	shlvl;
	bool	pwd;
	bool	last_cmd;

}	t_flag;

typedef struct s_data
{
	char	*tmp;
	char	**path_list;
	char	*user;
	char	**env;
	t_flag	flag;
}	t_data;

bool	init_env(char **envp, t_data *data);
void	cleanup(t_data *data);
char	*ft_extract_digits(char const *str);


//VERBOSE
void	print_env(t_data *data);

#endif
