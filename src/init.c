/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 07:55:12 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/26 18:35:34 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialisation de la struct t_redir
t_redir	*init_redir(void)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	if (!res)
		return (NULL);
	res->out = 0;
	res->in = 0;
	res->outout = 0;
	res->inin = 0;
	res->out_args = NULL;
	res->in_args = NULL;
	res->outout_args = NULL;
	res->inin_args = NULL;
	return (res);
}

static int	init_smcd(void)
{
	size_t	i;

	i = 0;
	g_fcmd->s_cmd = malloc(sizeof(t_scmd *) * g_fcmd->nb_scmd);
	if (!g_fcmd->s_cmd)
		return (clear_all());
	while (i < g_fcmd->nb_scmd)
	{
		g_fcmd->s_cmd[i] = malloc(sizeof(t_scmd));
		if (!g_fcmd->s_cmd[i])
			return (clear_all());
		g_fcmd->s_cmd[i]->ntokens = 0;
		g_fcmd->s_cmd[i]->child_id = 0;
		i++;
	}
	return (1);
}

// Initialize the big struct and fills some of its variable (f_cmd, nb_scmd, all s_cmd)
// Verifier t_scmd	*s_cmd ou t_scmd	**s_cmd
int	init_full_cmd(char *cmd)
{
	size_t	i;
	char	**cmd_split;

	g_fcmd = malloc(sizeof(t_fcmd));
	if (!g_fcmd)
		return (0);
	g_fcmd->f_cmd = cmd;
	g_fcmd->nb_scmd = countwords_quote((const char *)cmd, '|');
	if (!init_smcd())
		return (0);
	cmd_split = ft_split_quote(cmd, '|');
	if (!cmd_split)
		return (clear_all());
	i = 0;
	while (i < g_fcmd->nb_scmd)
	{
		g_fcmd->s_cmd[i]->s_cmd = remove_spaces(cmd_split[i]);
		if (!g_fcmd->s_cmd[i]->s_cmd)	// should clear cmd_split
			return (clear_all());
		g_fcmd->s_cmd[i]->redir = init_redir();
		if (!g_fcmd->s_cmd[i]->redir)	// should clear cmd_split
			return (clear_all());
		i++;
	}
	free (cmd_split);
	i = 0;
	return (1);
}
