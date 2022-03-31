/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:43:09 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/31 17:02:51 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns the env value of a given $variable
char	*get_env(char *str, size_t start, size_t end)
{
	char	*variable;
	t_env	*result;

	variable = ft_substr(str, start + 1, end - (start + 1));
	if (!variable)
		return (NULL);
	result = find_env(g_fcmd->envp, variable);
	free(variable);
	if (!result)
		return (NULL);
	return (result->value);
}

// norminette forces to split the function replace
static char	*insert_var(char *dest, char *src, size_t *i, size_t j)
{
	while (src && src[j])
	{
		dest[*i] = src[j];
		(*i)++;
		j++;
	}
	return (dest);
}

// in str replace $variable by $variable env's value
char	*replace_var(char *str, char *env, size_t start, size_t end)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(str) - (end - start) \
		+ ft_strlen(env) + 1);
	if (!dest)
		error_malloc(1);
	while (str && str[i] && i < start)
	{
		dest[i] = str[i];
		i++;
	}
	insert_var(dest, env, &i, 0);
	while (str && str[end])
	{
		dest[i] = str[end];
		i++;
		end++;
	}		
	dest[i] = '\0';
	free(str);
	return (dest);
}

char	*exit_code(char	*str, size_t i, size_t j)
{
	char	*exitcode;

	exitcode = ft_itoa(g_fcmd->exitcode);
	str = replace_var(str, exitcode, i, j + 1);
	free(exitcode);
	return (str);
}

size_t	end_var(char *str, size_t i, size_t j)
{
	while (str && str[j])
	{
		if (j + 1 == i && str[j] == '?')
			break ;
		if (j > i && !ft_isalpha((int) str[j]) && !ft_isdigit((int) str[j]))
			break ;
		j++;
	}
	return (j);
}
