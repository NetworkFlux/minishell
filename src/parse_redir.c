/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 08:23:20 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/23 13:51:58 by fcaquard         ###   ########.fr       */
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
		if (!redir->out_args || !redir->in_args
			|| !redir->outout_args
			|| !redir->inin_args)
			return (clear_all());
		fill_redir(g_fcmd->s_cmd[i]);
		i++;
	}
	return (1);
}

// Find if the redirection files have acces rights
int	redir_files_ok(t_scmd *scmd)
{
	if (scmd->redir->last_out == 1
		&& access(scmd->redir->out_args[scmd->redir->out - 1], W_OK) < 0)
	{
			scmd->redir->last_out = -1;
	}
	else if (scmd->redir->last_out == 2
		&& access(scmd->redir->outout_args[scmd->redir->outout - 1], W_OK) < 0)
	{
			scmd->redir->last_out = -1;
	}
	if (scmd->redir->in
		&& access(scmd->redir->in_args[scmd->redir->in - 1], R_OK) < 0)
	{
		scmd->redir->last_out = -1;
	}
	return (scmd->redir->last_out);
}
