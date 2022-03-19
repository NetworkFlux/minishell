/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:06:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/19 19:47:07 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_in_tab(t_scmd *s_cmd, int fd)
{
	char	**res;
	char	*line;
	int		new_fd = 0;

	(void)fd;
	line = NULL;
	//printf("Parent Process : Reading pipe fd : %d\n", fd);
	if (s_cmd->redir->in || s_cmd->redir->inin)
	{
		//printf("Parent Process : In or inin redirection asked\n");
		res = apply_inredir(s_cmd);
	}
	else
	{
		new_fd = open("temp.ms", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (!new_fd)
			return (NULL);
		while (get_next_line(fd, &line))
			ft_putendl_fd(line, new_fd);
		//printf("Parent Process : No in or inin redirection asked\n");
		res = s_cmd->tokens;
		res = ft_realloc(res, "temp.ms");
		close(new_fd);
		//printf("Parent Process : Pipe was read\n");
	}
	// int j = 0;
	// while (res[j])
	// 	printf("%s\n", res[j++]);
	return (res);
}

void	exec_full(size_t index, char **args)
{
	int		p1[2]; // p1[0] - read || p1[1] - write
	int		wstatus;

	// env list to array
	if (g_fcmd->env)
		free(g_fcmd->env);
	g_fcmd->env = env_listtoarray(g_fcmd->envp);

	if (find_builtin(g_fcmd->s_cmd[index]) == 0) // exit
			route_builtins(g_fcmd->s_cmd[index], 0);
	if (g_fcmd->exec_path)
		free(g_fcmd->exec_path);
	g_fcmd->exec_path = find_path(g_fcmd->s_cmd[index]);
	printf("<exec_full> target: |%s|\n", g_fcmd->exec_path); // remove

	pipe(p1);
	g_fcmd->child_id = fork();
	if (g_fcmd->child_id == 0)
	{
		// Child process
		int	redir_out;
		
		//printf("Child Process %ld : Process is starting\n", index + 1);
		close(p1[0]);
		//printf("Child Process %ld : Closing reading pipe (obvious)\n", index + 1);
		redir_out = apply_outredir(g_fcmd->s_cmd[index]);
		// redir_out == 1 if there is NO output redirection set (keep pointing to STDOUT)
		// redir_out == ? if there IS an output redirection set
		//printf("Child Process %ld : Output redirection set to %d\n", index + 1, redir_out);
		if (redir_out == 1 && index != g_fcmd->nb_scmd - 1)
		{
			// In this case, no output redirection are set but there is an other command
			// waiting for that output.
			// So we need to send the output to the main process using the pipe.
			//printf("Child Process %ld : STDOUT now goes to the pipe with fd %d\n", index + 1, p1[1]);
			dup2(p1[1], STDOUT_FILENO);
			// Now, what is supposed to be send to STDOUT will be send to the pipe.
		}
		else
		{
			// There are 3 scenarios here : 1. If redir_out is not set to 1 and it is not
			// the last command, it means that the output must be send to the output specified by redir_out.
			// 2. If redir_out is set to 1 and it is the last command, it means the the and of the program
			// so the output must be STDOUT unless specified/
			// 3. if redir_out is not set to 1 and it is the last command, it means the end of the program
			// but with a specific output set by redir_out.
			//printf("Child Process %ld : STDOUT now goes to the specified redirection\n", index + 1);
			if (redir_out != 1)
			{
				dup2(redir_out, STDOUT_FILENO);
				close(redir_out);	// If redir_out is 1, it is a bad idea to close STDOUT.
			}
			// Now the output will be the one specified by redir_out.
		}
		close(p1[1]);
		//printf("Child Process : Closing wrting pipe\n");
		is_builtin(g_fcmd->s_cmd[index], args, g_fcmd->exec_path);
		// close(fd[1]); // close child process fd 1 from builtin function
	}
	else
	{
		//printf("Parent Process %ld : Process is starting\n", index + 1);
		close(p1[1]);
		//printf("Parent Process %ld : Closing writing pipe (obvious)\n", index + 1);
		waitpid(g_fcmd->child_id, &wstatus, 0);
		if (WIFEXITED(wstatus))
		{
			printf("<exec_full> exitcode: %d\n",  WEXITSTATUS(wstatus));
			g_fcmd->exitcode = WEXITSTATUS(wstatus);
		}
		else
		{
			printf("<exec_full> Error: Child execution failed.\n");
		}
		g_fcmd->child_id = -1;
		//printf("Parent Process %ld : Waiting for child execution\n", index + 1);
		if (index != g_fcmd->nb_scmd - 1)
		{
			// If this is not the last command, we need to set args to the args of the next
			// command and execute this function again.
			//char	*line;
			//while (get_next_line(p1[0], &line))
				//printf("%s\n", line);
			//printf("Parent Process %ld : Reading pipe fd : %d\n", index + 1, p1[0]);
			args = find_in_tab(g_fcmd->s_cmd[index + 1], p1[0]);
			//printf("Parent Process %ld : Data traited from the pipe\n", index + 1);
			close(p1[0]);
			//printf("Parent Process %ld : Closing reading pipe\n", index + 1);
			//printf("Parent Process %ld : Launching next recursion\n", index + 1);
			exec_full(index + 1, args);
		}
		else
			close(p1[0]);
		unlink("temp.ms");
		unlink("heredoc.ms");
		printf("Parent Process %ld : End of execution\n", index + 1);
	}
	return ;
}
