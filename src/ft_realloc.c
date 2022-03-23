/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:10:34 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/23 13:33:13 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_copy(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**ft_realloc(char **tab, char *str)
{
	char	**res;
	int		size_tab;
	int		i;

	res = NULL;
	size_tab = 0;
	i = 0;
	while (tab[size_tab])
		size_tab++;
	res = malloc(sizeof(char *) * (size_tab + 2));
	if (!res)
		return (NULL);
	while (i < size_tab + 1)
	{
		if (i == size_tab)
			res[i] = ft_copy(str);
		else
			res[i] = ft_copy(tab[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
