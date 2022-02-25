/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 08:23:20 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/25 21:53:48 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ajoute chaque arg de redirection dans le tableau arg
// et retire cette redirection de la commande simple
void	add_redir_arg(t_scmd *s_cmd, unsigned int i, int j, char c)
{
	char	*temp_right;
	char	*temp_left;
	char	*temp;

	temp_left = ft_substr(s_cmd->s_cmd, 0, i);
	//printf("TEMP LEFT : %s\n", temp_left);
	temp_right = remove_spaces(ft_substr(s_cmd->s_cmd, i + 1, ft_strlen(s_cmd->s_cmd)));
	//printf("TEMP RIGHT : %s\n", temp_right);
	temp = first_word(temp_right);
	//printf("TEMP : %s\n", temp);
	if (c == '>')
		s_cmd->redir->out_args[j] = temp;
	else
		s_cmd->redir->in_args[j] = temp;
	temp_right += ft_strlen(temp);
	s_cmd->s_cmd = strcat(temp_left, remove_spaces(temp_right));
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
			&& (ft_isalnum(s_cmd->s_cmd[i + 2]) || s_cmd->s_cmd[i + 2] == ' '))
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
int	parse_redir(t_fcmd *f_cmd)
{
	size_t	i;

	i = 0;
	while (i < f_cmd->nb_scmd)
	{
		f_cmd->s_cmd[i]->redir->out = nb_redir(f_cmd->s_cmd[i]->s_cmd, '>');
		f_cmd->s_cmd[i]->redir->in = nb_redir(f_cmd->s_cmd[i]->s_cmd, '<');
		f_cmd->s_cmd[i]->redir->outout = nb_dredir(f_cmd->s_cmd[i]->s_cmd, '>');
		f_cmd->s_cmd[i]->redir->inin = nb_dredir(f_cmd->s_cmd[i]->s_cmd, '<');
		f_cmd->s_cmd[i]->redir->out_args = malloc(sizeof(char *) * f_cmd->s_cmd[i]->redir->out);
		if (!f_cmd->s_cmd[i]->redir->out_args)
			return (clear_all(f_cmd));
		f_cmd->s_cmd[i]->redir->in_args = malloc(sizeof(char *) * f_cmd->s_cmd[i]->redir->in);
		if (!f_cmd->s_cmd[i]->redir->in_args)
			return (clear_all(f_cmd));
		f_cmd->s_cmd[i]->redir->outout_args = malloc(sizeof(char *) * f_cmd->s_cmd[i]->redir->outout);
		if (!f_cmd->s_cmd[i]->redir->outout_args)
			return (clear_all(f_cmd));
		f_cmd->s_cmd[i]->redir->inin_args = malloc(sizeof(char *) * f_cmd->s_cmd[i]->redir->inin);
		if (!f_cmd->s_cmd[i]->redir->inin_args)
			return (clear_all(f_cmd));
		fill_redir(f_cmd->s_cmd[i]);
		i++;
	}
	return (1);
}