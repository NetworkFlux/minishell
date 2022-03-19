/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:49:31 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/19 18:14:37 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create an env list and populates it
static	t_env	*fill_env_list(char **envp, size_t i)
{
	char	**array;
	t_env	*env;

	env = malloc(sizeof(t_env) * 1);
	if (!env)
		error_malloc(1);
	array = split_once(envp[i], '=');
	if (!array)
		error_malloc(1);
	env->line = malloc (sizeof(char) * ft_strlen(envp[i]) + 1);
	if (!env->line)
		error_malloc(1);
	env->line[ft_strlen(envp[i])] = '\0';
	env->line = ft_strcopy(env->line, envp[i], 0);
	env->name = array[0];
	env->value = array[1];
	free(array);
	return (env);
}

// creates a linked list from *envp[]
t_env	*create_env(char **envp)
{
	size_t	i;
	t_env	*env;
	t_env	*prev;

	i = 0;
	prev = NULL;
	while (envp && envp[i])
	{
		env = fill_env_list(envp, i);
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
