/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 07:55:12 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/25 21:53:48 by fcaquard         ###   ########.fr       */
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

// Initialize the big struct and fills some of its variable (f_cmd, nb_scmd, all s_cmd)
// Verifier t_scmd	*s_cmd ou t_scmd	**s_cmd
t_fcmd	*init_full_cmd(char *cmd)
{
	t_fcmd	*res;
	size_t	i;
	char	**cmd_split;

	res = malloc(sizeof(t_fcmd));
	if (!res)
		return (NULL);
	res->f_cmd = cmd;
	printf("Full command : %s\n", res->f_cmd); //check
	res->nb_scmd = countwords_quote((const char *)cmd, '|');
	printf("Number of simple commands : %ld\n", res->nb_scmd); //check	
	res->s_cmd = malloc(sizeof(t_scmd *) * res->nb_scmd);
	if (!res->s_cmd)
		return (NULL);		// should free all above
	i = 0;
	while (i < res->nb_scmd)
	{
		res->s_cmd[i] = malloc(sizeof(t_scmd));
		if (!res->s_cmd[i++])
			return (NULL);	// should free all above
	}
	cmd_split = ft_split_quote(cmd, '|');
	if (!cmd_split)
		return (NULL);		// should free all above
	i = 0;
	while (i < res->nb_scmd)
	{
		res->s_cmd[i]->s_cmd = remove_spaces(cmd_split[i]);
		if (!res->s_cmd[i]->s_cmd)
			return (NULL);	// should free all above
		res->s_cmd[i]->redir = init_redir();
		if (!res->s_cmd[i]->redir)
			return (NULL);	// should free all above
		res->s_cmd[i]->ntokens = 0;
		i++;
	}
	free (cmd_split);

	// check
	i = 0;
	while (i < res->nb_scmd)
	{
		printf("Single command %ld : %s\n", i + 1, res->s_cmd[i]->s_cmd); //check
		i++;
	}
	return (res);
}
