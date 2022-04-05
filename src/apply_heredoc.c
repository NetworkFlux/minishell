/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:09:24 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/05 17:26:56 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unlink(t_scmd *s_cmd)
{
	char	*strcat;
	char	*strcat2;

	if (s_cmd->redir->inin > 0
		&& s_cmd->redir->inin_args && s_cmd->redir->inin_args[0])
	{
		strcat = ft_strcat(s_cmd->redir->inin_args[s_cmd->redir->inin - 1], \
			".ms");
		strcat2 = ft_strcat(".", strcat);
		if (s_cmd->redir->inin)
			unlink(strcat2);
		if (strcat)
			free(strcat);
		if (strcat2)
			free(strcat2);
	}
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
	char	**tmp;

	i = 0;
	while (i < g_fcmd->nb_scmd)
	{
		if (g_fcmd->s_cmd[i]->redir->inin)
		{
			tmp = apply_heredoc(g_fcmd->s_cmd[i]);
			if (g_fcmd->s_cmd[i]->tokens)
				clear_array(g_fcmd->s_cmd[i]->tokens, \
					ft_arrlen(g_fcmd->s_cmd[i]->tokens));
			g_fcmd->s_cmd[i]->tokens = tmp;
		}
		i++;
	}
	return ;
}
