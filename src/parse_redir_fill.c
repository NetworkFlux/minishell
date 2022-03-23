/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:50:27 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/23 13:51:03 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Remplie le tableau de la redirection simple c
static void	fill_s(t_scmd *s_cmd, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s_cmd->s_cmd[i])
	{
		if (s_cmd->s_cmd[i] == c && s_cmd->s_cmd[i + 1] != c
			&& !is_in_quote(s_cmd->s_cmd, i) && (ft_isalnum(s_cmd->s_cmd[i + 1])
				|| s_cmd->s_cmd[i + 1] == ' '))
		{
			if ((i == 0 || s_cmd->s_cmd[i - 1] != c))
			{
				add_redir_arg(s_cmd, i, j, c);
				j++;
			}
			else
				i++;
		}
		else
			i++;
	}
}

// Remplie le tableau de la redirection double (<< / >>) c
static void	fill_d(t_scmd *s_cmd, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s_cmd->s_cmd[i])
	{
		if (s_cmd->s_cmd[i] == c && s_cmd->s_cmd[i + 1] == c
			&& !is_in_quote(s_cmd->s_cmd, i) && s_cmd->s_cmd[i + 2]
			&& (ft_isalnum(s_cmd->s_cmd[i + 2])
				|| s_cmd->s_cmd[i + 2] == ' '))
		{
			add_dredir_arg(s_cmd, i, j, c);
			j++;
		}
		else
			i++;
	}
}

// Remplie le tableau d'arg pour chaque redirection
void	fill_redir(t_scmd *s_cmd)
{
	fill_s(s_cmd, '>');
	fill_s(s_cmd, '<');
	fill_d(s_cmd, '>');
	fill_d(s_cmd, '<');
}
