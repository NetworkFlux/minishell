/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:49:31 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/05 14:06:51 by fcaquard         ###   ########.fr       */
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

static char	**norminette_split(char **array, size_t i, char *str)
{
	array[0] = malloc(sizeof(char) * i + 1);
	if (!array[0])
	{
		free (array);
		error_malloc();
	}
	array[1] = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
	if (!array[1])
	{
		free (array[0]);
		free (array);
		error_malloc();
	}
	array[0] = fill_split(0, i, str, array[0]);
	array[1] = fill_split(i + 1, ft_strlen(str), str, array[1]);
	return (array);
}


char	**split_first_occurence(char *str, unsigned char c)
{
	char	**array;
	size_t	i;

	i = 0;
	array = malloc(sizeof(char *) * 2);
	if (!array)
		error_malloc();
	while (str && str[i])
	{
		if (str[i] == c)
		{
			array = norminette_split(array, i, str);
			break ;
		}
		i++;
	}
	return (array);
}
