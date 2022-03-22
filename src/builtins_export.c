/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/22 18:51:22 by fcaquard         ###   ########.fr       */
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
		str = malloc(sizeof(char) * ft_strlen(name) + \
			ft_strlen(value) + 4);
		if (!str)
			return (0);
		str = strrebuild(name, "=", value);
		g_fcmd->envp = add_env(g_fcmd->envp, name, value, str);
	}
	return (1);
}

int	insert_update_env(char *name, char *value)
{
	t_env	*tmp;

	tmp = find_env(g_fcmd->envp, name);
	if (!tmp)
	{
		return (export_new(name, value));
	}
	else
	{
		tmp->name = name;
		tmp->value = value;
	}
	return (1);
}

int		builtins_export(t_scmd *scmd, int readpipe)
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
		errno = EINVAL;
		perror("bash: export");
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
