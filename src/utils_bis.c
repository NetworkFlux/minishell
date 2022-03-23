/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:32:54 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/23 18:32:55 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	fills dest with the content of src from the position `start` to `end`
//	returns at least '\0'
char	*fillstr(size_t start, size_t end, const char *src)
{
	size_t	i;
	size_t	size;
	char	*dest;

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
	array[0] = fillstr(0, i, str);
	if (!array[0])
	{
		free(array);
		return (NULL);
	}
	array[1] = fillstr(i + 1, ft_strlen(str), str);
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
