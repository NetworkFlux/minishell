/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exec_full.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:06:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/23 13:25:42 by fcaquard         ###   ########.fr       */
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
	{
		exit(EXIT_FAILURE);
	}
}

void	child(int p1[2], size_t index, int readpipe)
{
	int		redir_out;

	close(p1[0]);
	if (!g_fcmd->s_cmd[index]->redir->in && !g_fcmd->s_cmd[index]->redir->inin && readpipe)
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

void	parent(int p1[2], size_t index)
{
	int	wstatus;
	
	close(p1[1]);
	waitpid(g_fcmd->child_id, &wstatus, 0);
	g_fcmd->child_id = -1;
	if (WIFEXITED(wstatus))
		g_fcmd->exitcode = WEXITSTATUS(wstatus);

	if (index != g_fcmd->nb_scmd - 1)
	{
		// args = find_in_tab(g_fcmd->s_cmd[index + 1], p1[0]);
		//close(p1[0]);
	}
	else
	{
		close(p1[0]);
	}
	
}

int		pipeline(t_scmd	*scmd, void(foutput)(t_scmd *), int readpipe)
{
	// printf("-- builtin pipeline\n");
	int		p1[2]; // p1[0] - read || p1[1] - write

	pipe(p1);
	g_fcmd->child_id = fork();
	if (g_fcmd->child_id == 0)
	{
		child(p1, scmd->index, readpipe);
		foutput(scmd);
	}
	else
	{
		parent(p1, scmd->index);
	}
	return (p1[0]);
	// printf("-- builtin pipeline end\n");
}

void	__exec_full(size_t index, char **args, int readpipe)
{
	int		builtin;
	int		needpipe;
	int		new_piperead;

	needpipe = 0;
	new_piperead = 0;
	// updates env in case export was previously called
	if (g_fcmd->env)
		clear_array(g_fcmd->env, ft_arrlen(g_fcmd->env));
	g_fcmd->env = env_listtoarray(g_fcmd->envp, env_len(g_fcmd->envp), 0);

	// get path to exec (NULL if not found)
	if (g_fcmd->exec_path)
	{
		free(g_fcmd->exec_path);
		g_fcmd->exec_path = NULL;
	}
	g_fcmd->exec_path = find_path(g_fcmd->s_cmd[index]);

	if (!g_fcmd->s_cmd[index]->redir->in && !g_fcmd->s_cmd[index]->redir->inin && index != g_fcmd->nb_scmd - 1)
		needpipe = 1;
	// check if the command is a builtin
	builtin = find_builtin(g_fcmd->s_cmd[index]);
	if (builtin != -1)
	{
		// returns args from pipe~parent or NULL from main process 
		new_piperead = route_builtins(g_fcmd->s_cmd[index], builtin, readpipe);
	}
	else
	{
		// returns args from pipe~parent
		new_piperead = pipeline(g_fcmd->s_cmd[index], &execute, readpipe);
	}
	if (index != g_fcmd->nb_scmd - 1)
	{
		if (!args)
			args = g_fcmd->s_cmd[index + 1]->tokens;
		// print_array(args, "next args");
		if (!needpipe)
			new_piperead = 0;
		__exec_full(index + 1, args, new_piperead);
	}
	return ;
}
