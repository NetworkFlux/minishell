/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:38:18 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/25 14:28:48 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retourne le nombre de redirection double (>> / <<) c valide
int	nb_dredir(char *str, char c)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] == c
			&& !is_in_quote(str, i) && (ft_isalnum(str[i + 2])
				|| str[i + 2] == ' '))
			res++;
		i++;
	}
	return (res);
}

// Retourne le nombre de redirection simple c valide
int	nb_redir(char *str, char c)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c
			&& !is_in_quote(str, i) && (ft_isalnum(str[i + 1])
				|| str[i + 1] == ' '))
			if ((i == 0 || str[i - 1] != c))
				res++;
		i++;
	}
	return (res);
}

// Ajoute chaque arg de redirection dans le tableau arg
// et retire cette redirection de la commande simple
void	add_dredir_arg(t_scmd *s_cmd, unsigned int i, int j, char c)
{
	char	*temp_right;
	char	*temp_left;
	char	*temp;
	char	*word;

	temp = ft_substr(s_cmd->s_cmd, i + 2, ft_strlen(s_cmd->s_cmd));
	temp_right = remove_spaces(temp);
	word = first_word(temp_right);
	if (c == '>')
		s_cmd->redir->outout_args[j] = remove_spaces(word);
	else
		s_cmd->redir->inin_args[j] = remove_spaces(word);
	free(temp);
	temp = temp_right;
	temp_right += ft_strlen(word);
	free(word);
	word = remove_spaces(temp_right);
	temp_left = ft_substr(s_cmd->s_cmd, 0, i);
	free(s_cmd->s_cmd);
	s_cmd->s_cmd = ft_strcat(temp_left, word);
	free(temp);
	free(word);
	free(temp_left);
}

// Trouve si la derniere redirection d'input est simple ou double
int	find_last_in(char *str)
{
	size_t	i;
	int		res;

	res = 0;
	if (str[0] && str[0] == '<' && str[1] && str[1] == '<'
		&& !is_in_quote(str, 0))
		res = 2;
	i = 2;
	while (str[i])
	{
		if (str[i] == '<' && str[i - 1] != '<' && !is_in_quote(str, i))
			res = 1;
		else if (str[i] == '<' && str[i - 1] == '<' && !is_in_quote(str, i))
			res = 2;
		i++;
	}
	return (res);
}

// Trouve si la derniere redirection d'output est simple ou double
int	find_last_out(char *str)
{
	size_t	i;
	int		res;

	res = 0;
	if (str[0] && str[0] == '>' && str[1] && str[1] == '>'
		&& !is_in_quote(str, 0))
		res = 2;
	i = 2;
	while (str[i])
	{
		if (str[i] == '>' && str[i - 1] != '>' && !is_in_quote(str, i))
			res = 1;
		else if (str[i] == '>' && str[i - 1] == '>' && !is_in_quote(str, i))
			res = 2;
		i++;
	}
	return (res);
}
