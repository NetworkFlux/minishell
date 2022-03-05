/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 07:55:12 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/05 12:06:57 by npinheir         ###   ########.fr       */
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
	res->last_out = 0;
	return (res);
}

static int	init_smcd(void)
{
	size_t	i;

	i = 0;
	g_fcmd->s_cmd = malloc(sizeof(t_scmd) * g_fcmd->nb_scmd);
	if (!g_fcmd->s_cmd)
		return (clear_all());
	while (i < g_fcmd->nb_scmd)
	{
		g_fcmd->s_cmd[i] = malloc(sizeof(t_scmd));
		if (!g_fcmd->s_cmd[i])
			return (clear_all());
		g_fcmd->s_cmd[i]->s_cmd = NULL;
		g_fcmd->s_cmd[i]->exec = NULL;
		g_fcmd->s_cmd[i]->tokens = NULL;
		g_fcmd->s_cmd[i]->instructions = NULL;
		g_fcmd->s_cmd[i]->ntokens = 0;
		g_fcmd->s_cmd[i]->child_id = 0;
		i++;
	}
	return (1);
}

static char	**free_split(char **split)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd)
	{
		free (split[i]);
		i++;
	}
	free (split);
	return (NULL);
}

// Initialize the big struct and fills some of its variable (f_cmd, nb_scmd, all s_cmd)
// Verifier t_scmd	*s_cmd ou t_scmd	**s_cmd
int	init_full_cmd(char *cmd)
{
	size_t	i;
	char	**cmd_split;

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
		if (!g_fcmd->s_cmd[i]->s_cmd)
		{
			free_split(cmd_split);
			return (clear_all());
		}
		g_fcmd->s_cmd[i]->redir = init_redir();
		if (!g_fcmd->s_cmd[i]->redir)
		{
			free_split(cmd_split);
			return (clear_all());
		}
		i++;
	}
	cmd_split = free_split(cmd_split);
	i = 0;
	return (1);
}
