/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:07 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/19 18:14:56 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns the env value of a given $variable
static char	*get_env(char *str, size_t start, size_t end)
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
static char	*replace(char *str, char *env, size_t start, size_t end)
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
static char	*exit_code(char	*str, size_t i, size_t j)
{
	char *exitcode;
	
	exitcode = ft_itoa(g_fcmd->exitcode);
	str = replace(str, exitcode, i, j + 1);
	free(exitcode);
	return (str);
}

// search for a $variable then replace it by its env value
static char	*find_variable(char *str, size_t i, size_t j)
{
	if (str && str[i])
	{
		if (str[i] == '\'')
		{
			i += 1;
			while (str && str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '$')
		{
			j = i + 1;
			while (str && str[j])
			{
				if (j - 1 == i && str[j] == '?')
					break ;
				if (!ft_isalpha((int) str[j]) && !ft_isdigit((int) str[j]))
					break ;
				j++;
			}
			if (j - i >= 1)
			{
				if (str[j] == '?')
				{
					str = exit_code(str, i, j);
				}
				else
					str = replace(str, get_env(str, i, j), i, j);
				find_variable(str, 0, 0);
			}
		}
	}
	return (str);
}

// entry point for the search and replacement of env $variables
void	env_variables(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		g_fcmd->s_cmd[i]->s_cmd = find_variable(g_fcmd->s_cmd[i]->s_cmd, 0, 0);
		i++;
	}
	return ;
}
