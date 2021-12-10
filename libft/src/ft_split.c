/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 08:12:19 by npinheir          #+#    #+#             */
/*   Updated: 2021/11/01 13:45:07 by npinheir         ###   ########.fr       */
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

static int	countwords(char const *s, char c)
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
		if (s[i - 1] == c && s[i] != c)
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
		while (s[j] && s[j] != c)
			res[index][i++] = s[j++];
		res[index][i] = '\0';
		index++;
	}
	res[index] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = countwords(s, c);
	res = malloc(sizeof(char *) * (nb_words + 1));
	if (!res)
		return (NULL);
	res = fill_tab(s, c, nb_words, res);
	return (res);
}
