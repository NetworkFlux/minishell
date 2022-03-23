/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:28:32 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/23 18:29:35 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_scmd *s_cmd)
{
	char	**args;

	if (s_cmd->redir->in || s_cmd->redir->inin)
		args = apply_inredir(s_cmd);
	else
		args = s_cmd->tokens;
	if (g_fcmd->exec_path == NULL)
	{
		write(2, s_cmd->tokens[0], ft_strlen(s_cmd->tokens[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	if (execve(g_fcmd->exec_path, args, g_fcmd->env) == -1)
		exit(EXIT_FAILURE);
}

static void	child(int p1[2], size_t index, int readpipe)
{
	int		redir_out;

	close(p1[0]);
	if (!g_fcmd->s_cmd[index]->redir->in
		&& !g_fcmd->s_cmd[index]->redir->inin && readpipe)
	{
		dup2(readpipe, STDIN_FILENO);
		close(readpipe);
	}
	redir_out = apply_outredir(g_fcmd->s_cmd[index]);
	if (redir_out == 1 && index != g_fcmd->nb_scmd - 1)
		dup2(p1[1], STDOUT_FILENO);
	else if (redir_out != 1)
	{
		dup2(redir_out, STDOUT_FILENO);
		close(redir_out);
	}
	close(p1[1]);
}

static void	parent(int p1[2], size_t index)
{
	size_t	i;
	int		wstatus;

	wstatus = 0;
	i = 0;
	close(p1[1]);
	if (index == g_fcmd->nb_scmd - 1)
	{
		while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
		{
			waitpid(g_fcmd->s_cmd[i]->pid, &wstatus, 0);
			g_fcmd->s_cmd[i]->pid = -1;
			if (WIFEXITED(wstatus))
				g_fcmd->exitcode = WEXITSTATUS(wstatus);
			i++;
		}
		close(p1[0]);
	}
}

int	pipeline(t_scmd	*scmd, void (foutput)(t_scmd *), int readpipe)
{
	int		p1[2];

	pipe(p1);
	scmd->pid = fork();
	if (scmd->pid == 0)
	{
		child(p1, scmd->index, readpipe);
		foutput(scmd);
	}
	else
		parent(p1, scmd->index);
	return (p1[0]);
}
