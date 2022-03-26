/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/26 13:45:13 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// called from child process
void	output_envp(t_scmd *scmd)
{
	(void)scmd;
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

static int	export_new(char *name, char *value)
{
	char	*str;

	if (ft_strlen(name))
	{
		str = strrebuild(name, "=", value);
		if (!str)
			return (0);
		add_env(g_fcmd->envp, name, value, str);
	}
	return (1);
}

int	insert_update_env(char *name, char *value, int is_cd)
{
	t_env	*tmp;

	tmp = find_env(g_fcmd->envp, name);
	if (!tmp)
		return (export_new(name, value));
	else
	{
		if (!is_cd)
		{
			free(name);
			free(tmp->value);
		}
		tmp->value = NULL;
		tmp->value = ft_strdup(value);
		g_fcmd->envp = tmp;
		if (!is_cd)
			free(value);
	}
	return (1);
}

int	builtins_export(t_scmd *scmd, int readpipe)
{
	char	**array;

	if (scmd->tokens && scmd->ntokens == 1)
		return (pipeline(scmd, &output_envp, readpipe));
	if (!scmd->tokens[1])
		return (0);
	array = split_once(scmd->tokens[1], '=');
	if (!array)
		error_malloc(1);
	if (!ft_strisalpha(array[0]))
	{
		clear_array(array, ft_arrlen(array));
		perr(EINVAL, "bash: export");
		return (0);
	}
	if (!insert_update_env(array[0], array[1]))
	{
		clear_array(array, ft_arrlen(array));
		error_malloc(1);
	}
	clear_array(array, ft_arrlen(array));
	return (0);
}
