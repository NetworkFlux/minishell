/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:32:20 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/24 18:54:06 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_prepare(size_t index)
{
	if (g_fcmd->env)
		clear_array(g_fcmd->env, ft_arrlen(g_fcmd->env));
	g_fcmd->env = env_listtoarray(g_fcmd->envp, env_len(g_fcmd->envp), 0);
	if (g_fcmd->exec_path)
	{
		free(g_fcmd->exec_path);
		g_fcmd->exec_path = NULL;
	}
	g_fcmd->exec_path = find_path(g_fcmd->s_cmd[index]);
}

void	__exec_full(size_t index, char **args, int readpipe)
{
	int		builtin;
	int		needpipe;
	int		new_piperead;

	size_t	i;
	int	wstatus;

	i = 0;
	wstatus = 0;
	needpipe = 0;
	new_piperead = 0;
	exec_prepare(index);
	if (!g_fcmd->s_cmd[index]->redir->in
		&& !g_fcmd->s_cmd[index]->redir->inin && index != g_fcmd->nb_scmd - 1)
		needpipe = 1;
	builtin = find_builtin(g_fcmd->s_cmd[index]);
	if (builtin != -1)
		new_piperead = route_builtins(g_fcmd->s_cmd[index], builtin, readpipe);
	else
		new_piperead = pipeline(g_fcmd->s_cmd[index], &execute, readpipe);
	if (index != g_fcmd->nb_scmd - 1)
	{
		if (!args)
			args = g_fcmd->s_cmd[index + 1]->tokens;
		if (!needpipe)
			new_piperead = 0;
		__exec_full(index + 1, args, new_piperead);
	}
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		waitpid(g_fcmd->s_cmd[i]->pid, &wstatus, 0);
		g_fcmd->s_cmd[i]->pid = -1;
		if (WIFEXITED(wstatus))
			g_fcmd->exitcode = WEXITSTATUS(wstatus);
		i++;
	}
	return ;
}
