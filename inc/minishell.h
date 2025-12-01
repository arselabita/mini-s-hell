/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:26:38 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/01 05:08:17 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE

# ifndef VERBOSE
#  define VERBOSE 0
# endif

# define CMD 0			//for t_cmds struct
# define ARGS 1			//for t_cmds struct

#define ERROR 1
#define OK_EXIT 0
#define RESET 424242

# ifndef DEBUG_ALLOC
#  define DEBUG_ALLOC 0
# endif

# define PWD 0
# define SHLVL 1
# define LAST_CMD 2

# define TOKEN_REDIR_IN 0
# define TOKEN_REDIR_OUT 1
# define TOKEN_REDIR_APPEND 2
# define TOKEN_REDIR_HEREDOC 3
# define TOKEN_PIPE 4
# define TOKEN_WORD 5

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

// FREE
// data->env ------> free_split  		**char of environment variables**
// data->path_list  -----> free_split 	**for PATH variable split by ':'**
// data->redirs -----> free_redirs		**linked list of redirections
// rdirs->filename -----> free()		**filename or delimiter string**
// data->cmd ------> free_cmds			**linked list of commands**
// data->cmd->argv -----> free_split	**array of command and arguments**
// data->exec.heredoc_files				**array of tmp heredoc_filenames



typedef enum e_redir_type
{
    REDIR_IN,        // <
    REDIR_OUT,       // >
    REDIR_APPEND,    // >>
    REDIR_HEREDOC    // <<
}   t_redir_type;



typedef struct Token
{
	int 			typ;  //WORD, PIPE, REDIR_IN, REDIR_OUT, APPEND, HEREDOC
	char			*content; //string, "ls", "-l", "out.txt"
	struct Token	*next;
}	t_token;



typedef struct flag
{
	bool	shlvl;
	bool	pwd;
	bool	last_cmd;
	bool	redirect_fail;
	bool	abort;				// for heredoc interruption

}	t_flag;

typedef struct fildescriptor
{
	int	curr[2];
	int	prev[2];
}	t_fds;

typedef struct redirections
{
	int					typ;
	char				*filename;
	bool				heredoc;	// ARESLA needs to set the flag! if REDIR_HEREDOC/ TOKEN_HERDOC
	struct redirections	*next;
}	t_redirs;


typedef struct cmds
{
	char		**argv;
	t_redirs	*redirs;
	bool		pipe_after;			// ARESLA needs to set the flag! is there a pipe comming after cmd? last cmd has no pipe after, always false
	struct cmds	*next;
}	t_cmds;

typedef struct list
{
	int		size;			//ARESELA has to count each t_cmds node with data->list.size++;
	t_cmds	*head;
	t_cmds	*tail;
}	t_stack;

typedef struct heredocs
{
	char	**files; 	// array of heredoc filenames to be unlinked at the end
	int		count;		// ARSLEA needs to count up in parsing heredoc_count++ // number of heredoc files created
	int		index;
}	t_heredoc;

typedef struct execute
{
	char	**search_paths;
	char	*path;

}	t_exec;

typedef struct s_data
{
	char		*tmp;
	char		**path_list;
	char		*user;
	char		**env;
	uint		return_value;		// handle in expander for echo $?


	t_fds		fd;
	t_exec		exec;
	t_cmds		*cmd;
	t_stack		list;
	t_flag		flag;
	t_heredoc	heredoc;
}	t_data;


// GLOBAL VAR
extern volatile sig_atomic_t g_signal;

// START
bool	init_env(char **envp, t_data *data);
void	cleanup(t_data *data, int exit_code);
char	*ft_extract_digits(char const *str);

//EXECUTION
void	single_cmd(t_data *data, t_cmds *cmd);
void	handle_errno(t_data *data, t_cmds *cmd, int error_code);
void	child_cleanup(int exit_code, char *message, t_data *data, t_cmds *cmd);
void	handle_redirections(t_data *data, t_cmds *cmd);
void	executor(t_cmds *cmd, t_data *data); ////DELETE LATER, JUST DEBUG
void	multi_cmds(t_data *data, t_cmds *cmd);
//void	executor(char *line, t_data *data); // FINAL one
void	ft_close(t_data *data);
void	get_exit_status(t_data *data, int pid);
void	exec_cmd(t_data *data, t_cmds *cmd);
int		heredocs(t_data *data, t_cmds *cmd);

//CLEANUP
void    free_split(char **split);
void    redirs_lstclear(t_redirs **lst);
void    cmd_lstclear(t_cmds **lst);
void	reset_readline(t_data *data);


//SIGNALS
void	prompt_handler(int sig);
void	*init_signals_prompt(void);
void	heredoc_handler(int sig);
void	init_signals_heredoc(void);


//VERBOSE
void	print_env(t_data *data);
void	init_single_command_struct(t_data *data);
void	*debug_build_commands(t_data *data);
void	print_cmd_list(t_cmds *head);




#endif
