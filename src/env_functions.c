/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:49:31 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/04 18:50:46 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*fill_split(size_t start, size_t end, const char *src, char *dest)
{
	size_t	i;

	i = 0;
	while (start < end && src && src[start])
	{
		dest[i] = src[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**split_first_occurence(char *str, unsigned char c)
{
	char	**array;
	size_t	i;

	i = 0;
	array = malloc(sizeof(char *) * 2);
	if (!array)
		return (NULL); // todo;
	while (str && str[i])
	{
		if (str[i] == c)
		{
			array[0] = malloc(sizeof(char) * i + 1);
			if (!array[0])
				return (NULL); // todo: clear properly
			array[1] = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
			if (!array[1])
				return (NULL); // todo: clear properly
			array[0] = fill_split(0, i, str, array[0]);
			array[1] = fill_split(i + 1, ft_strlen(str), str, array[1]);
			break ;
		}
		i++;
	}
	return (array);
}
