/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:07 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/28 15:44:34 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO should clear and exit;
static char	*get_env(char *str, size_t start, size_t end)
{
	char	*variable;
	char	*result;

	variable = ft_substr(str, start + 1, end - (start + 1));
	if (!variable)
		return (NULL);
	result = getenv(variable);
	printf("<get_env> variable: |%s|\n", variable);
	free(variable);
	return (result);
}

// norminette forces to split the function
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

// TODO should clear and exit;
static char	*replace(char *str, char *env, size_t start, size_t end)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(str) - (end - start) \
		+ ft_strlen(env) + 1);
	if (!dest)
		return (NULL);
	while (str && str[i] && i < start)
	{
		dest[i] = str[i];
		i++;
	}
	insert_var (dest, env, &i, 0);
	while (str && str[end])
	{
		dest[i] = str[end];
		i++;
		end++;
	}		
	dest[i] = '\0';
	debug_env(env, str, dest);
	return (dest);
}

/* if a variable is found $something (at least one char after $)
sends it to be replaced by its environment variable 
try:	>`export test="echo 'blabla'"`
		>$test
		>echo "hello $test"
	skip single quoted content
*/
static char	*find_variable(char *str, size_t i, size_t j)
{
	while (str && str[i])
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
				if (!ft_isalpha((int) str[j]) && !ft_isdigit((int) str[j]))
					break ;
				j++;
			}
			if (j - i > 1)
				str = replace(str, get_env(str, i, j), i, j);
			i = j;
		}
		i++;
	}
	return (str);
}

// look for $
// then look for its end 
// anything not [A-a,0-9] is the end
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
