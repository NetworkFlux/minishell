/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:05:57 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/19 18:22:19 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//	fills dest with the content of src from the position `start` to `end`
//	returns at least '\0'
char	*fillstr(size_t start, size_t end, const char *src, char *dest)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = end - start;
	if (start > end)
		size = 0;
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (start < end && src && src[start])
	{
		dest[i] = src[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

//	"str0(separator char)str1" array[2] IS NULL
char	**split_once(char *str, char c)
{
	size_t	i;
	char	**array;

	i = find_char(str, c);
	array = malloc(sizeof(char *) * (2 + 1));
	if (!array)
		return (NULL);
	array[2] = NULL;
	array[0] = fillstr(0, i, str, array[0]);
	if (!array[0])
	{
		free(array);
		return (NULL);
	}
	array[1] = fillstr(i + 1, ft_strlen(str), str, array[1]);
	if (!array[1])
	{
		free(array[0]);
		free(array);
		return (NULL);
	}
	return (array);
}

// copy src into dest starting at a given dest position
// Does not NULL terminate dest
char	*ft_strcopy(char *dest, char *src, size_t index_dest)
{
	size_t	i;

	i = 0;
	while (dest && src && src[i])
	{
		dest[index_dest] = src[i];
		index_dest++;
		i++;
	}
	return (dest);
}

int	clear_array(char **array, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free (array[i]);
		i++;
	}
	free(array);
	return (1);
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

// get size of NULL terminated char **
size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
