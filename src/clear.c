/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:11:33 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/17 17:27:42 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_redir(t_redir *redir)
{
	if (redir->in_args)
		free(redir->in_args);
	if (redir->inin_args)
		free(redir->inin_args);
	if (redir->out_args)
		free(redir->out_args);
	if (redir->outout_args)
		free(redir->outout_args);
	free(redir);
}

static void	clear_tokens(t_scmd *scmd)
{
	size_t	i;

	i = 0;
	while (i < scmd->ntokens && scmd->tokens[i])
		free(scmd->tokens[i++]);
	free(scmd->tokens);
}

/*	loops over single command in order to free its content 
	kill command's child process if still running (pid!=0) */
static void	clear_scmd(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd)
	{
		if (g_fcmd->s_cmd[i]->instructions)
			free(g_fcmd->s_cmd[i]->instructions);
		if (g_fcmd->s_cmd[i]->ntokens > 0)
			clear_tokens(g_fcmd->s_cmd[i]);
		if (g_fcmd->s_cmd[i]->redir)
			clear_redir(g_fcmd->s_cmd[i]->redir);
		free(g_fcmd->s_cmd[i]->s_cmd);
		free(g_fcmd->s_cmd[i]);
		i++;
	}
}

void	clear_env(void)
{
	t_env	*tmp;
	t_env	*current;

	current = env_first(g_fcmd->envp);
	while (current)
	{
		free(current->name);
		free(current->value);
		free(current->line);
		if (!current->next)
			break ;
		tmp = current;
		current = current->next;
		free(tmp);
	}
	free(current);
	current = NULL;
}

/*
g_fcmd t_fcmd *
	f_cmd	char *
	envp	t_env * (chained list)
		name	char *
		value	char *
	s_cmd	t_scmd **
		smcd	char *
		exec	char *
		instructions	char *
		tokens	t_tokens **
			token	char *
		redir	t_redir *
			out_args		char **
			out_out_args	char **
			in_args			char **
			in_in_args		char **
*/

/* dives into our command tree and tries to free everything */
int	clear_all(void)
{
	if (g_fcmd)
	{
		if (g_fcmd->child_id != -1)
		{
			printf("killing child process: %d\n", g_fcmd->child_id);
			kill (g_fcmd->child_id, SIGKILL);
			g_fcmd->child_id = -1;
		}
		else
		{
			if (g_fcmd->s_cmd)
			{
				if (g_fcmd->s_cmd[0])
					clear_scmd();
				free(g_fcmd->s_cmd);
				g_fcmd->s_cmd = NULL;
			}
			g_fcmd->nb_scmd = 0;
			free(g_fcmd->f_cmd);
			g_fcmd->f_cmd = NULL;
			printf("<clear_all> global cleared !\n");
		}
	}
	return (0);
}
