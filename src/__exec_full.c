/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exec_full.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:06:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/21 14:45:42 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_in_tab(t_scmd *s_cmd, int fd)
{
	char	**res;
	char	*line;
	int		new_fd = 0;

	line = NULL;
	if (s_cmd->redir->in || s_cmd->redir->inin)
	{
		res = apply_inredir(s_cmd);
	}
	else
	{
		new_fd = open("./temp.ms", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (!new_fd)
			return (NULL);
		while (get_next_line(fd, &line))
			ft_putendl_fd(line, new_fd);
		res = s_cmd->tokens;
		res = ft_realloc(res, "./temp.ms");
		close(new_fd);
	}
	return (res);
}

void	execute(t_scmd *s_cmd, char **args)
{
	if (s_cmd->redir->in || s_cmd->redir->inin)
		args = apply_inredir(s_cmd);
	if (g_fcmd->exec_path == NULL)
	{
		printf("%s: command not found\n", s_cmd->tokens[0]);
		exit(127);
	}
	if (execve(g_fcmd->exec_path, args, g_fcmd->env) == -1)
	{
		exit(EXIT_FAILURE);
	}
}

void	child(int p1[2], size_t index)
{
	int		redir_out;
		
	close(p1[0]);
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

char	**parent(int p1[2], size_t index, char **args)
{
	int	wstatus;
	
	close(p1[1]);
	waitpid(g_fcmd->child_id, &wstatus, 0);
	g_fcmd->child_id = -1;
	if (WIFEXITED(wstatus))
		g_fcmd->exitcode = WEXITSTATUS(wstatus);
	if (index != g_fcmd->nb_scmd - 1)
	{
		printf("--- parent looking for args\n");
		args = find_in_tab(g_fcmd->s_cmd[index + 1], p1[0]);
		close(p1[0]);
		return (args);
	}
	else
	{
		printf("--- parent ending command\n");
		close(p1[0]);
	}
	unlink("temp.ms");
	unlink("heredoc.ms");
	return (NULL);
}

char	**pipeline(t_scmd	*scmd, char **args, void(foutput)(t_scmd *, char **))
{
	// printf("-- builtin pipeline\n");
	int		p1[2]; // p1[0] - read || p1[1] - write

	pipe(p1);
	g_fcmd->child_id = fork();
	if (g_fcmd->child_id == 0)
	{
		child(p1, scmd->index);
		foutput(scmd, args);
	}
	else
	{
		args = parent(p1, scmd->index, args);
	}
	return (args);
	// printf("-- builtin pipeline end\n");
}

void	__exec_full(size_t index, char **args)
{
	int		builtin;

	// updates env in case export was previously called
	if (g_fcmd->env)
		free(g_fcmd->env);
	g_fcmd->env = env_listtoarray(g_fcmd->envp);

	// get path to exec (NULL if not found)
	if (g_fcmd->exec_path) 
		free(g_fcmd->exec_path);
	g_fcmd->exec_path = find_path(g_fcmd->s_cmd[index]);

	// check if the command is a builtin
	builtin = find_builtin(g_fcmd->s_cmd[index]);
	if (builtin != -1)
	{
		// returns args from pipe~parent or NULL from main process 
		args = route_builtins(g_fcmd->s_cmd[index], builtin, args);
	}
	else
	{
		// returns args from pipe~parent
		args = pipeline(g_fcmd->s_cmd[index], args, &execute);
	}
	if (index != g_fcmd->nb_scmd - 1)
	{
		if (!args)
			args = g_fcmd->s_cmd[index + 1]->tokens;
		print_array(args, "recur args");
		__exec_full(index + 1, args);
	}
	return ;
}
