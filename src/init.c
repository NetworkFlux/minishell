/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 07:55:12 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/31 18:48:54 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialisation de la struct t_redir
t_redir	*init_redir(void)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	if (!res)
		error_malloc(1);
	res->out = 0;
	res->in = 0;
	res->outout = 0;
	res->inin = 0;
	res->out_args = NULL;
	res->in_args = NULL;
	res->outout_args = NULL;
	res->inin_args = NULL;
	res->last_out = 0;
	res->last_in = 0;
	return (res);
}

void	init_global(char **envp)
{
	g_fcmd = malloc(sizeof(t_fcmd));
	if (!g_fcmd)
		error_malloc(1);
	g_fcmd->env = NULL;
	g_fcmd->f_cmd = NULL;
	g_fcmd->active_heredoc = 0;
	g_fcmd->s_cmd = NULL;
	g_fcmd->exitcode = 0;
	g_fcmd->exec_path = NULL;
	g_fcmd->envp = create_env(envp);
}

static int	init_smcd(void)
{
	size_t	i;

	i = 0;
	g_fcmd->s_cmd = malloc(sizeof(t_scmd) * g_fcmd->nb_scmd);
	if (!g_fcmd->s_cmd)
		error_malloc(1);
	while (i < g_fcmd->nb_scmd)
	{
		g_fcmd->s_cmd[i] = malloc(sizeof(t_scmd));
		if (!g_fcmd->s_cmd[i])
			error_malloc(1);
		g_fcmd->s_cmd[i]->index = i;
		g_fcmd->s_cmd[i]->pid = -1;
		g_fcmd->s_cmd[i]->s_cmd = NULL;
		g_fcmd->s_cmd[i]->tokens = NULL;
		g_fcmd->s_cmd[i]->instructions = NULL;
		g_fcmd->s_cmd[i]->ntokens = 0;
		i++;
	}
	return (1);
}

// Initialize the big struct and fills some of 
// its variable (f_cmd, nb_scmd, all s_cmd)
// Verifier t_scmd	*s_cmd ou t_scmd	**s_cmd
int	init_full_cmd(char *cmd)
{
	size_t	i;
	char	**cmd_split;

	i = 0;
	g_fcmd->nb_scmd = countwords_quote((const char *)cmd, '|');
	init_smcd();
	cmd_split = ft_split_quote(cmd, '|');
	if (!cmd_split)
		error_malloc(1);
	while (i < g_fcmd->nb_scmd)
	{
		g_fcmd->s_cmd[i]->s_cmd = remove_spaces(cmd_split[i]);
		if (!g_fcmd->s_cmd[i]->s_cmd)
			error_malloc(clear_array(cmd_split, g_fcmd->nb_scmd));
		g_fcmd->s_cmd[i]->redir = init_redir();
		if (!g_fcmd->s_cmd[i]->redir)
			error_malloc(clear_array(cmd_split, g_fcmd->nb_scmd));
		i++;
	}
	clear_array(cmd_split, g_fcmd->nb_scmd);
	return (1);
}
