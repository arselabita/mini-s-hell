/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 04:14:17 by pjelinek          #+#    #+#             */
/*   Updated: 2025/12/01 05:13:57 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ======================================================== */
/*   Redirect-Typ aus User-Input (< > << >>) bestimmen      */
/* ======================================================== */
static int	parse_redir_type(const char *sym)
{
	if (strcmp(sym, "<") == 0)
		return (REDIR_IN);
	if (strcmp(sym, ">") == 0)
		return (REDIR_OUT);
	if (strcmp(sym, ">>") == 0)
		return (REDIR_APPEND);
	if (strcmp(sym, "<<") == 0)
		return (REDIR_HEREDOC);
	return (-1);
}

/* ======================================================== */
/*   Redirect-Linked-List erstellen                         */
/*   Gibt bei Fehler alles frei und NULL zurück             */
/* ======================================================== */
static t_redirs	*build_redirs(int count, t_data *data)
{
	t_redirs	*head;
	t_redirs	*cur;
	t_redirs	*node;
	char		symbol[3];
	char		filename[256];
	int			i;

	if (count <= 0)
		return (NULL);
	head = NULL;
	cur = NULL;
	i = 0;
	while (i < count)
	{
		printf("  Redirect %d Symbol (< > << >>): ", i + 1);
		if (scanf("%2s", symbol) != 1)
		{
			redirs_lstclear(&head);
			return (NULL);
		}
		printf("  Redirect %d Filename/Delimiter: ", i + 1);
		if (scanf("%255s", filename) != 1)
		{
			redirs_lstclear(&head);
			return (NULL);
		}
		node = ft_calloc(1, sizeof(t_redirs));
		if (!node)
		{
			redirs_lstclear(&head);
			return (NULL);
		}
		node->typ = parse_redir_type(symbol);
		if (node->typ == REDIR_HEREDOC)
		{
			node->heredoc = true;
			data->heredoc.count++;
		}
		node->filename = ft_strdup(filename);
		if (!node->filename)
		{
			free(node);
			redirs_lstclear(&head);
			return (NULL);
		}
		node->next = NULL;
		if (!head)
			head = node;
		else
			cur->next = node;
		cur = node;
		i++;
	}
	return (head);
}


void *debug_build_commands(t_data *data)
{
    int     count;
    int     i;
    char    cmd[128];
    char    arg[128];
    int     redir_count;
    t_cmds *node;

    printf("\n");
    printf("Number of Commands (0-9): ");
    if (scanf("%d", &count) != 1 || count <= 0)
        return NULL;

    i = 0;
    while (i < count)
    {
        printf("\nCommand %d — Name: ", i + 1);
        if (scanf("%127s", cmd) != 1)
        {
            cmd_lstclear(&data->list.head);
            data->list.tail = NULL;
            data->list.size = 0;
            data->cmd = NULL;
            return NULL;
        }
        printf("Command %d — Argument ('0' = NULL): ", i + 1);
        if (scanf("%127s", arg) != 1)
        {
            cmd_lstclear(&data->list.head);
            data->list.tail = NULL;
            data->list.size = 0;
            data->cmd = NULL;
            return NULL;
        }

        node = ft_calloc(1, sizeof(t_cmds));
        if (!node)
        {
            cmd_lstclear(&data->list.head);
            data->list.tail = NULL;
            data->list.size = 0;
            data->cmd = NULL;
            return NULL;
        }
        node->argv = ft_calloc(3, sizeof(char *));
        if (!node->argv)
        {
            free(node);
            cmd_lstclear(&data->list.head);
            data->list.tail = NULL;
            data->list.size = 0;
            data->cmd = NULL;
            return NULL;
        }
        node->argv[0] = ft_strdup(cmd);
        if (!node->argv[0])
        {
            free_split(node->argv);
            free(node);
            cmd_lstclear(&data->list.head);
            data->list.tail = NULL;
            data->list.size = 0;
            data->cmd = NULL;
            return NULL;
        }
        if (strcmp(arg, "0") == 0)
            node->argv[1] = NULL;
        else
        {
            node->argv[1] = ft_strdup(arg);
            if (!node->argv[1])
            {
                free_split(node->argv);
                free(node);
                cmd_lstclear(&data->list.head);
                data->list.tail = NULL;
                data->list.size = 0;
                data->cmd = NULL;
                return NULL;
            }
        }
        node->argv[2] = NULL;

        printf("Command %d — Number of Redirects: ", i + 1);
        if (scanf("%d", &redir_count) != 1)
        {
            free_split(node->argv);
            free(node);
            cmd_lstclear(&data->list.head);
            data->list.tail = NULL;
            data->list.size = 0;
            data->cmd = NULL;
            return NULL;
        }
        node->redirs = build_redirs(redir_count, data);
        if (redir_count > 0 && !node->redirs)
        {
            free_split(node->argv);
            free(node);
            cmd_lstclear(&data->list.head);
            data->list.tail = NULL;
            data->list.size = 0;
            data->cmd = NULL;
            return NULL;
        }

        /* in data->list einhängen */
        node->next = NULL;
        node->pipe_after = false;
        if (!data->list.head)
        {
            data->list.head = node;
            data->list.tail = node;
        }
        else
        {
            data->list.tail->pipe_after = true;
            data->list.tail->next = node;
            data->list.tail = node;
        }
        data->list.size++;
        i++;
    }

    /* Alias, damit dein Executor weiter mit data->cmd arbeiten kann */
    data->cmd = data->list.head;
	return NULL; /* wird nie erreicht, nur für den Compiler */
}



/* ======================================================== */
/*   VERBOSE: Print the entire command list structure       */



static const char *redir_type_to_str(int type)
{
    if (type == REDIR_IN)
        return "REDIR_IN";
    if (type == REDIR_OUT)
        return "REDIR_OUT";
    if (type == REDIR_APPEND)
        return "REDIR_APPEND";
    if (type == REDIR_HEREDOC)
        return "REDIR_HEREDOC";
    return "UNKNOWN";
}


static void print_one_cmd(t_cmds *cmd, int idx)
{
    int     i;
    t_redirs *r;

    printf("cmd %d\n", idx);
    printf("  t_cmd\n");

    i = 0;
    if (cmd->argv)
    {
        while (cmd->argv[i])
        {
            printf("    argv[%d] -> \"%s\"\n", i, cmd->argv[i]);
            i++;
        }
    }
    else
        printf("    argv: (null)\n");

    r = cmd->redirs;
    i = 0;
    while (r)
    {
        printf("\n  t_redirs[%d]\n", i);
        printf("    type     -> %s\n", redir_type_to_str(r->typ));
        printf("    filename -> \"%s\"\n", r->filename ? r->filename : "(null)");
        r = r->next;
        i++;
    }
    if (!cmd->redirs)
        printf("  (no Redirections)\n");

    if (cmd->pipe_after)
        printf("\n  PIPE  ---> cmd %d\n", idx + 1);

    printf("\n");
}

void print_cmd_list(t_cmds *head)
{
    int   i;
    t_cmds *cur;

    puts("======= PARSED COMMAND STRUCTURE =======\n");
    cur = head;
    i = 1;
    while (cur)
    {
        print_one_cmd(cur, i);
        cur = cur->next;
        i++;
    }
    puts("========================================");
}
