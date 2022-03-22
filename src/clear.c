/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:11:33 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 16:23:45 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_redir(t_redir *redir)
{
	if (redir->in_args)
		clear_array(redir->in_args, redir->in);
	if (redir->inin_args)
		clear_array(redir->inin_args, redir->inin);
	if (redir->out_args)
		clear_array(redir->out_args, redir->out);
	if (redir->outout_args)
		clear_array(redir->outout_args, redir->outout);
	free(redir);
}

static void	clear_tokens(t_scmd *scmd)
{
	size_t	i;

	i = 0;
	while (i < scmd->ntokens && scmd->tokens[i])
	{
		free(scmd->tokens[i]);
		i++;
	}
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
		if (g_fcmd->s_cmd[i]->s_cmd)
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
	if (g_fcmd->env)
		clear_array(g_fcmd->env, ft_arrlen(g_fcmd->env));
}

/*
g_fcmd t_fcmd *
	f_cmd	char *
	env		char **
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
int	kill_child(void)
{
	if (g_fcmd)
	{
		if (g_fcmd->child_id != -1)
		{
			kill(g_fcmd->child_id, SIGTERM);
			g_fcmd->exitcode = 128 + (int) SIGINT;
			g_fcmd->child_id = -1;
			return (1);
		}	
	}
	return (0);
}


int	clear_all(void)
{
	if (g_fcmd)
	{
		kill_child();
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
	}
	return (0);
}
