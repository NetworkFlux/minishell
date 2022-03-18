/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 08:07:29 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/18 20:04:03 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retourne le primier mot d'un str
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
	while (str[i] && !ft_isspace(str[i]))
		i++;
	res = malloc(sizeof(char) * (i - j + 1));
	if (!res)
		return (NULL);
	i = j;
	j = 0;
	while (str[i] && !ft_isspace(str[i]))
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

// compares 2 strings. 1 if same, 0 if not
int	ft_strcompare(const char *str, char *test)
{
	size_t	i;

	i = 0;
	while (str && str[i] && test && test[i])
	{
		if (str[i] != test[i])
			return (0);
		i++;
	}
	if (str[i] != test[i])
		return (0);
	return (1);
}

/*
size_t	charsslen(int fd)
{
	size_t	res;
	char	*line;

	res = 0;
	while (get_next_line(fd, &line) > 0)
		res++;
	close(fd);
	return (res + 1);
}
*/

char	**realloc_heredoc(char **tab, size_t res_len, char *input)
{
	char	**res;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char *) * (res_len + 1));
	if (!res)
		return (NULL); // gere l'erreur
	while (i < res_len - 1)
	{
		res[i] = malloc(sizeof(char) * (ft_strlen(tab[i]) + 1));
		if (!res[i])
			return (NULL); // gerer l'erreur
		res[i] = tab[i];
		res[i][ft_strlen(tab[i])] = '\0';
		i++;
	}
	res[i] = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!res[i])
			return (NULL); // gerer l'erreur
	res[i] = input;
	res[i++][ft_strlen(input)] = '\0';
	res[i] = NULL;
	return (res);
}

// get size of NULL terminated char **
size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
