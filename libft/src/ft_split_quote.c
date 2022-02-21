/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 08:12:19 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/21 09:24:48 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function allocates and returns an array
	of strings obtained by splitting ’s’ using the
	character ’c’ as a delimiter. The array must be
	ended by a NULL pointer.	*/

static char	**ft_malloc_error(char **res)
{
	int	i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
	return (NULL);
}

static int	quote_check(const char *s, int index)
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
	return (!(s_quote || d_quote));
}

int	countwords_quote(char const *s, char c)
{
	int	count;
	int	i;

	if (!s || !s[0])
		return (0);
	count = 0;
	if (s[0] != c)
		count = 1;
	i = 1;
	while (s[i])
	{
		if ((s[i - 1] == c && s[i] != c) && quote_check(s, i - 1))
			count++;
		i++;
	}
	return (count);
}

static char	**fill_tab(char const *s, char c, int nb_words, char **res)
{
	int	index;
	int	i;
	int	j;

	index = 0;
	j = 0;
	while (index < nb_words)
	{
		i = 0;
		res[index] = malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (!res[index])
			return (ft_malloc_error(res));
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && (s[j] != c || !quote_check(s, j)))
			res[index][i++] = s[j++];
		res[index][i] = '\0';
		index++;
	}
	res[index] = NULL;
	return (res);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**res;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = countwords_quote(s, c);
	res = malloc(sizeof(char *) * (nb_words + 1));
	if (!res)
		return (NULL);
	res = fill_tab(s, c, nb_words, res);
	return (res);
}