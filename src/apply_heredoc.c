/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:09:24 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/03 18:24:01 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unlink(t_scmd *s_cmd)
{
	if (s_cmd->redir->inin)
		unlink(ft_strcat(".",
				ft_strcat(s_cmd->redir->inin_args[s_cmd->redir->inin - 1],
					".ms")));
}

int	check_outputs2(t_scmd *s_cmd)
{
	size_t	i;
	DIR		*temp;

	i = 0;
	temp = NULL;
	while (i < s_cmd->redir->outout)
	{
		temp = opendir(s_cmd->redir->outout_args[i]);
		if (temp)
		{
			printf("bash: %s: Is a directory\n", s_cmd->redir->outout_args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_outputs(t_scmd *s_cmd)
{
	size_t	i;
	DIR		*temp;

	i = 0;
	temp = NULL;
	while (i < s_cmd->redir->out)
	{
		temp = opendir(s_cmd->redir->out_args[i]);
		if (temp)
		{
			printf("bash: %s: Is a directory\n", s_cmd->redir->out_args[i]);
			return (1);
		}
		i++;
	}
	if (check_outputs2(s_cmd))
		return (1);
	return (0);
}

void	apply_hd(t_fcmd *g_fcmd)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd)
	{
		if (g_fcmd->s_cmd[i]->redir->inin)
			g_fcmd->s_cmd[i]->tokens = apply_heredoc(g_fcmd->s_cmd[i]);
		i++;
	}
	return ;
}
