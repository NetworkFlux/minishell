/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.42.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:11:33 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/28 12:03:14 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear_array(char **array, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (1);
}

static void	clear_env(void)
{
	t_env	*tmp;
	t_env	*current;

	current = env_first(g_fcmd->envp);
	while (current)
	{
		free(current->name);
		free(current->value);
		free(current->line);
		if (!current->next)
			break ;
		tmp = current;
		current = current->next;
		free(tmp);
	}
	free(current);
	current = NULL;
	if (g_fcmd->env)
	{
		clear_array(g_fcmd->env, ft_arrlen(g_fcmd->env));
	}
}

// kill all remaining child processes
// return 1 if a child has been terminated
int	kill_child(void)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	if (g_fcmd && g_fcmd->s_cmd)
	{
		while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
		{
			if (g_fcmd->s_cmd[i]->pid != -1)
			{
				kill(g_fcmd->s_cmd[i]->pid, SIGQUIT);
				g_fcmd->s_cmd[i]->pid = -1;
				res = 1;
			}
			i++;
		}
	}
	return (res);
}

void	clear_exit(int n)
{
	clear_all();
	clear_env();
	free(g_fcmd);
	g_fcmd = NULL;
	exit(n);
}
