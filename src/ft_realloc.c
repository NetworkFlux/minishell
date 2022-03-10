/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:10:34 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/10 12:27:56 by npinheir         ###   ########.fr       */
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
	size_tab = 1;
	i = 0;
	while (tab[i][0] != '\0')
		i++;
	size_tab += i;
	i = 0;
	res = malloc(sizeof(char *) * (size_tab + 1));
	if (!res)
		return (NULL);
	while (i < size_tab - 1)
	{
		res[i] = ft_copy(tab[i]);
		i++;
	}
	res[i] = ft_copy(str);
	res[i + 1] = "\0";
	//free_realloc(tab);
	return (res);
}