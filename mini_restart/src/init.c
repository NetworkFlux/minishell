/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 07:55:12 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/25 10:13:13 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialisation de la struct redir_t
redir_t	*init_redir(void)
{
	redir_t	*res;

	res = malloc(sizeof(redir_t));
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
// Verifier s_cmd_t	*s_cmd ou s_cmd_t	**s_cmd
f_cmd_t	*init_full_cmd(char *cmd)
{
	f_cmd_t	*res;
	size_t	i;
	char	**cmd_split;

	res = malloc(sizeof(f_cmd_t));
	if (!res)
		return (NULL);
	res->f_cmd = cmd;
	printf("Full command : %s\n", res->f_cmd); //check
	res->nb_scmd = countwords_quote((const char *)cmd, '|');
	printf("Number of simple commands : %ld\n", res->nb_scmd); //check	
	res->s_cmd = malloc(sizeof(s_cmd_t *) * res->nb_scmd);
	if (!res->s_cmd)
		return (NULL);
	i = 0;
	while (i < res->nb_scmd)
		res->s_cmd[i++] = malloc(sizeof(s_cmd_t));
	cmd_split = ft_split_quote(cmd, '|');
	i = 0;
	while (i < res->nb_scmd)
	{
		res->s_cmd[i]->s_cmd = remove_spaces(cmd_split[i]);
		res->s_cmd[i]->redir = init_redir();
		if (!res->s_cmd[i]->redir)
			return (NULL);
		i++;
	}

	// check
	i = 0;
	while (i < res->nb_scmd)
	{
		printf("Single command %ld : %s\n", i + 1, res->s_cmd[i]->s_cmd); //check
		i++;
	}
	return (res);
}
