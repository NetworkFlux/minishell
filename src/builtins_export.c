/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/15 19:08:54 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(void)
{
	g_fcmd->envp = env_first(g_fcmd->envp);
	while (g_fcmd->envp)
	{
		printf("declare -x %s=\"%s\"\n", g_fcmd->envp->name, g_fcmd->envp->value);
		if (!g_fcmd->envp->next)
			break ;
		g_fcmd->envp = g_fcmd->envp->next;
	}
}

static int	valid_input(t_scmd *scmd)
{
	if (scmd->tokens && scmd->ntokens == 1)
	{
		print_envp();
		return (0);
	}
	if (!scmd->tokens[1])
	{
		printf ("Error arguments.\n");
		return (0);
	}
	return (1);
}

static void	export_new(char **array)
{
	char	*str;
	
	if (ft_strlen(array[0]))
	{
		str = malloc(sizeof(char) * ft_strlen(array[0]) + ft_strlen(array[1]) + 4);
		if (!str)
			error_malloc();
		str = strrebuild(array[0], " = ",array[1]);
		g_fcmd->envp = add_env(g_fcmd->envp, array[0], array[1], str);
	}
	else
	{
		if (ft_strlen(array[1]))
			printf("bash: export: `=%s': not a valid identifier\n", array[1]);
	}
	free(array);
}

static void	export_update(t_env *tmp, char **array)
{
	tmp->name = array[0];
	tmp->value = array[1];
	free(array);
}

void	builtins_export(t_scmd *scmd)
{
	char	**array;
	t_env	*tmp;

	if (!valid_input(scmd))
		return ;
	array = split_first_occurence(scmd->tokens[1], '=');
	if (!array)
		error_malloc();
	printf("name: |%s| \nva: |%s|\n", array[0], array[1]);
	tmp = find_env(g_fcmd->envp, array[0]);
	if (!tmp)
		export_new(array);
	else
		export_update(tmp, array);
}
