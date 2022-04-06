/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:28:32 by fcaquard          #+#    #+#             */
/*   Updated: 2022/04/07 00:29:47 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_scmd *s_cmd)
{
	char	**args;

	args = s_cmd->tokens;
	if (s_cmd->redir->last_in)
		apply_inredir(s_cmd);
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
	if (check_outputs(g_fcmd->s_cmd[index]))
		exit(1);
	redir_out = apply_outredir(g_fcmd->s_cmd[index]);
	redir_out = apply_outredir2(g_fcmd->s_cmd[index], redir_out);
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
	wait(NULL);
	close(p1[1]);
	if (index == g_fcmd->nb_scmd - 1)
		close(p1[0]);
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
