/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:35:07 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/04 19:24:24 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (NULL); // todo: clear properly
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

// TODO should clear and exit;
// returns the env value of a given word
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
	// printf("<get_env> variable: |%s|\n", result->value);
	return (result->value);
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