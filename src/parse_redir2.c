/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:38:18 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/25 21:53:36 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retourne le nombre de redirection double (>> / <<) c valide
int		nb_dredir(char *str, char c)
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
int		nb_redir(char *str, char c)
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

	temp_left = ft_substr(s_cmd->s_cmd, 0, i);
	//printf("TEMP LEFT : %s\n", temp_left);
	temp_right = remove_spaces(ft_substr(s_cmd->s_cmd, i + 2, ft_strlen(s_cmd->s_cmd)));
	//printf("TEMP RIGHT : %s\n", temp_right);
	temp = first_word(temp_right);
	//printf("TEMP : %s\n", temp);
	if (c == '>')
		s_cmd->redir->outout_args[j] = temp;
	else
		s_cmd->redir->inin_args[j] = temp;
	temp_right += ft_strlen(temp);
	s_cmd->s_cmd = strcat(temp_left, remove_spaces(temp_right));
}