/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:20:42 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/31 17:01:56 by fcaquard         ###   ########.fr       */
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
		if (g_fcmd->exec_path)
		{
			free(g_fcmd->exec_path);
			g_fcmd->exec_path = NULL;
		}
		g_fcmd->nb_scmd = 0;
		if (g_fcmd->f_cmd)
			free(g_fcmd->f_cmd);
		g_fcmd->f_cmd = NULL;
	}
	return (0);
}
