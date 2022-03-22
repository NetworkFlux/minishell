/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 08:23:20 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/22 16:43:17 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ajoute chaque arg de redirection dans le tableau arg
// et retire cette redirection de la commande simple
void	add_redir_arg(t_scmd *s_cmd, unsigned int i, int j, char c)
{
	char	*right;
	char	*left;
	char	*temp;
	char	*temp2;

	left = ft_substr(s_cmd->s_cmd, 0, i);
	temp = ft_substr(s_cmd->s_cmd, i + 1, ft_strlen(s_cmd->s_cmd));
	right = remove_spaces(temp);
	temp2 = first_word(right);
	if (c == '>')
		s_cmd->redir->out_args[j] = remove_spaces(temp2);
	else
		s_cmd->redir->in_args[j] = remove_spaces(temp2);
	free(temp);
	temp = right;
	right += ft_strlen(temp2);
	free(temp2);
	temp2 = remove_spaces(right);
	free(s_cmd->s_cmd);
	s_cmd->s_cmd = ft_strcat(left, temp2);
	free(temp);
	free(temp2);
	free(left);
}

// Remplie le tableau de la redirection simple c
void	fill_s(t_scmd *s_cmd, char c)
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
void	fill_d(t_scmd *s_cmd, char c)
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

// Cette fonction trouve le nombre de chaque redirection et malloc les args
int	parse_redir(void)
{
	size_t	i;
	t_redir	*redir;

	i = 0;
	while (i < g_fcmd->nb_scmd)
	{
		redir = g_fcmd->s_cmd[i]->redir;
		redir->out = nb_redir(g_fcmd->s_cmd[i]->s_cmd, '>');
		redir->in = nb_redir(g_fcmd->s_cmd[i]->s_cmd, '<');
		redir->outout = nb_dredir(g_fcmd->s_cmd[i]->s_cmd, '>');
		redir->inin = nb_dredir(g_fcmd->s_cmd[i]->s_cmd, '<');
		redir->out_args = malloc(sizeof(char *) * redir->out);
		redir->in_args = malloc(sizeof(char *) * redir->in);
		redir->outout_args = malloc(sizeof(char *) * redir->outout);
		redir->inin_args = malloc(sizeof(char *) * redir->inin);
		redir->last_out = find_last_out(g_fcmd->s_cmd[i]->s_cmd);
		redir->last_in = find_last_in(g_fcmd->s_cmd[i]->s_cmd);
		if (!redir->out_args
			|| !redir->in_args
			|| !redir->outout_args
			|| !redir->inin_args)
			return (clear_all());
		fill_redir(g_fcmd->s_cmd[i]);
		i++;
	}
	return (1);
}
