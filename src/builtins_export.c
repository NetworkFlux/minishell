/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/21 14:45:11 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// called from child process
void	output_envp(t_scmd *scmd, char **args)
{
	(void)scmd;
	(void)args;
	g_fcmd->envp = env_first(g_fcmd->envp);
	while (g_fcmd->envp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(g_fcmd->envp->name, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(g_fcmd->envp->value, 1);
		if (!g_fcmd->envp->next)
			break ;
		g_fcmd->envp = g_fcmd->envp->next;
	}
	exit(0);
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
}

static void	export_update(t_env *tmp, char **array)
{
	tmp->name = array[0];
	tmp->value = array[1];
	free(array);
}

char **builtins_export(t_scmd *scmd, char **args)
{
	char	**array;
	t_env	*tmp;

	if (scmd->tokens && scmd->ntokens == 1)
	{
		args = pipeline(scmd, args, &output_envp);
		return (NULL);
	}
	if (!scmd->tokens[1])
		return (NULL);
	array = split_once(scmd->tokens[1], '=');
	if (!array)
		error_malloc(1);
	if (!ft_strisalpha(array[0]))
	{
		printf("bash: export: `%s': not a valid identifier\n", array[0]);
		return (NULL);
	}
	tmp = find_env(g_fcmd->envp, array[0]);
	if (!tmp)
		export_new(array);
	else
		export_update(tmp, array);
	return (NULL);
}
