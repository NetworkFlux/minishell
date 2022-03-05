/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:49:31 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/05 15:05:44 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fill_split(size_t start, size_t end, const char *src, char *dest)
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

// creates a linked list from *envp[]
t_env	*create_env(char **envp)
{
	size_t	i;
	t_env	*env;
	t_env	*prev;
	char	**array;

	i = 0;
	prev = NULL;
	while (envp && envp[i])
	{
		env = malloc(sizeof(t_env) * 1);
		if (!env)
			error_malloc();
		array = split_first_occurence(envp[i], '=');
		env->name = array[0];
		env->value = array[1];
		free(array);
		env->next = NULL;
		env->prev = prev;
		if (prev)
			prev->next = env;
		prev = env;
		env = env->next;
		i++;
	}
	return (env_first(prev));
}
