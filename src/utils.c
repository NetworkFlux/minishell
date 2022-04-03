/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 08:07:29 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/03 19:05:07 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retourne le premier mot d'un str
char	*first_word(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	j = i;
	while (str[i] && (!ft_isspace(str[i]) && str[i] != '>' && str[i] != '<'))
		i++;
	res = malloc(sizeof(char) * (i - j + 1));
	if (!res)
		return (NULL);
	i = j;
	j = 0;
	while (str[i] && (!ft_isspace(str[i]) && str[i] != '>' && str[i] != '<'))
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

// Return 1 if the caracter at index index is between simple or double quotes
int	is_in_quote(const char *s, int index)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (i < index)
	{
		if (s[i] == 39)
		{
			if (!d_quote)
				s_quote = !s_quote;
		}
		else if (s[i] == '"')
		{
			if (!s_quote)
				d_quote = !d_quote;
		}
		i++;
	}
	return (s_quote || d_quote);
}

// Removes spaces if str starts spaces
char	*remove_spaces(char *str)
{
	size_t	j;
	size_t	k;
	char	*temp;

	j = 0;
	k = 0;
	if (!str)
		return (NULL);
	while (str[j] && str[j] == ' ')
		j++;
	temp = malloc(sizeof(char) * ft_strlen(str) + 1 - j);
	if (!temp)
		return (NULL);
	while (str[j])
	{
		temp[k] = str[j];
		j++;
		k++;
	}
	temp[k] = '\0';
	return (temp);
}

// checks if the string provided is only alphanumerical
int	ft_strisalpha(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// counts until if finds char c
size_t	find_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}
