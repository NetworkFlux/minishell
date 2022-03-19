/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/19 18:11:01 by fcaquard         ###   ########.fr       */
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
		exit(0);
	}
	if (!scmd->tokens[1])
	{
		printf ("Error arguments.\n"); // remove
		exit(1);
	}
	return (1);
}

static void	export_new(char **array)
{
	char	*str;

	if (ft_strlen(array[0]))
	{
		str = malloc(sizeof(char) * ft_strlen(array[0]) + \
			ft_strlen(array[1]) + 4);
		if (!str)
			error_malloc(1);
		str = strrebuild(array[0], "=", array[1]);
		g_fcmd->envp = add_env(g_fcmd->envp, array[0], array[1], str);
	}
	clear_array(array, ft_arrlen(array));
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

	valid_input(scmd);
	array = split_once(scmd->tokens[1], '=');
	if (!array)
		error_malloc(1);
	if (!ft_strisalpha(array[0]))
	{
		printf("bash: export: `%s': not a valid identifier\n", array[0]);
		exit(1);
	}
	tmp = find_env(g_fcmd->envp, array[0]);
	if (!tmp)
		export_new(array);
	else
		export_update(tmp, array);
	exit(0);
}
