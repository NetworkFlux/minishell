/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:11:33 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/23 13:45:23 by fcaquard         ###   ########.fr       */
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

/* dives into our command tree and tries to free everything */
int	kill_child(void)
{
	if (g_fcmd)
	{
		if (g_fcmd->child_id != -1)
		{
			kill(g_fcmd->child_id, SIGTERM);
			g_fcmd->exitcode = 128 + (int) SIGINT;
			g_fcmd->child_id = -1;
			return (1);
		}	
	}
	return (0);
}

void	clear_exit(int n)
{
	clear_all();
	clear_env();
	free(g_fcmd);
	g_fcmd = NULL;
	exit(n);
}
