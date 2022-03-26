/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:44:45 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/25 23:59:58 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_first(t_env *env)
{
	while (env)
	{
		if (!env->prev)
			break ;
		env = env->prev;
	}
	return (env);
}

t_env	*env_last(t_env *env)
{
	while (env)
	{
		if (!env->next)
			break ;
		env = env->next;
	}
	return (env);
}

t_env	*find_env(t_env *env, char *name)
{
	env = env_first(env);
	while (env)
	{
		if (ft_strcompare(env->name, name))
			return (env);
		if (!env->next)
			break ;
		env = env->next;
	}
	if (env->name == name)
		return (env);
	return (NULL);
}

int	add_env(t_env *env, char *name, char *value, char *line)
{
	t_env	*new;

	env = env_last(env);
	new = malloc(sizeof(t_env) * 1);
	if (!new)
		return (0);
	new->name = malloc(sizeof(char) * ft_strlen(name) + 1);
	if(!new->name)
		return(0);
	new->name = ft_strcpy(new->name, name);
	new->value = malloc(sizeof(char) * ft_strlen(value) + 1);
	if(!new->value)
		return(0);
	new->value = ft_strcpy(new->value, value);
	new->line = line;
	new->next = NULL;
	new->prev = env;
	if (env)
		env->next = new;
	return (1);
}

t_env	*remove_env(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	if (env->next)
	{
		env->next->prev = env->prev;
		tmp = env->next;
	}
	if (env->prev)
	{
		env->prev->next = env->next;
		tmp = env->prev;
	}
	if (env->value)
		free(env->value);
	if (env->name)
		free(env->name);
	if (env->line)
		free(env->line);
	free(env);
	env = NULL;
	return (tmp);
}
