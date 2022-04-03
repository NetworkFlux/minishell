/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/04/03 19:41:06 by npinheir         ###   ########.fr       */
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

int	insert_update_env(char *name, char *value)
{
	t_env	*tmp;

	tmp = find_env(g_fcmd->envp, name);
	if (!tmp)
		return (export_new(name, value));
	else
	{
		free(tmp->value);
		tmp->value = NULL;
		tmp->value = ft_strdup(value);
		g_fcmd->envp = tmp;
	}
	return (1);
}

static void	export_norm(t_scmd *scmd, char **array)
{
	size_t	i;

	i = 1;
	while (scmd->tokens[i])
	{
		if (export_args(scmd->tokens[i]))
		{
			if (export_args(scmd->tokens[i]) == 1)
				perr(EINVAL, "bash: export");
			i++;
			continue ;
		}
		array = split_once(scmd->tokens[i], '=');
		if (!array)
			error_malloc(1);
		if (!ft_strisalpha(array[0]))
		{
			clear_array(array, ft_arrlen(array));
			perr(EINVAL, "bash: export");
			i++;
			continue ;
		}
		export_norm2(array);
		i++;
	}
}

int	builtins_export(t_scmd *scmd, int readpipe)
{
	char	**array;

	array = NULL;
	if (scmd->tokens && scmd->ntokens == 1)
		return (pipeline(scmd, &output_envp, readpipe));
	if (!scmd->tokens[1])
		return (0);
	export_norm(scmd, array);
	return (0);
}
