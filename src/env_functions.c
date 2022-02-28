/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:49:31 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/28 19:51:26 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns the desired environment variable value
// otherwise NULL
char	*get_variable_value(char *str)
{
	size_t	i;
	size_t	start;
	char	*value;

	i = 0;
	if (str && str[0])
	{
		while (g_fcmd->envp[i])
		{
			start = find_env_variable(g_fcmd->envp[i], str);
			if (start != 0)
			{
				value = ft_substr(g_fcmd->envp[i], start, ft_strlen(g_fcmd->envp[i]) - start);
				return (value);
			}
			i++;
		}
	}
	return (NULL);
}

// returns the start of the value (after `=`) if found
// otherwise 0
int	find_env_variable(char *stack, char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (stack && needle && stack[i])
	{
		j = 0;
		if (stack[i] == needle[j])
		{
			while (stack[i] && needle[j] 
				&& stack[i] == needle[j])
			{
				i++;
				j++;
			}
			if (needle[j] == '\0' && stack[i] == '=')
				return (i + 1);
			i -= j;
		}
		i++;
	}
	return (0);
}
