/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:06:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/17 20:59:00 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static char	*concat(char *first, char *append)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new = malloc (sizeof(char) * ft_strlen(first) + ft_strlen(append) + 1);
	if (!new)
		error_malloc(1);
	while (first && first[i])
	{
		new[j] = first[i];
		i++;
		j++;
	}
	i = 0;
	while (append && append[i])
	{
		new[j] = append[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}*/

/*	if exec isn't a builtin execute it 
	using fork and execve */
/*void	exec(t_scmd *scmd, t_env *env)
{
	char	*target;
	char	**envp;

	envp = env_listtoarray(env);
	print_env_array(envp);

	printf("<exec> |%s|\n", scmd->tokens[0]);
	scmd->child_id = fork();
	if (scmd->child_id == -1)
	{
		printf("<exec> fork failed\n");
		return ;
	}
	if (scmd->child_id == 0) // in fork
	{
		printf("<exec> in child process sleep()\n");
		target = concat("/usr/bin/", scmd->tokens[0]);
		printf("<exec> target: %s\n", target);
		if (execve(target, scmd->tokens, envp) == -1)
		{
			printf ("execve Error\n");
		}
		exit(0); // terminates the fork
	}
	else	// in main process
	{
		printf("<exec> in main process %d\n", scmd->child_id);
		waitpid(scmd->child_id, NULL, 0); // waits for the child to terminate
		scmd->child_id = 0;
		printf("<exec> after waiting %d\n", scmd->child_id);
	}
	printf("<exec> after fork\n");
	clear_array(envp, envp_len(envp));
}
*/

char	**find_in_tab(t_scmd *s_cmd, int fd)
{
	char	**res;
	char	*line;

	line = NULL;
	if (s_cmd->redir->in || s_cmd->redir->inin)
		res = apply_inredir(s_cmd);
	else
	{
		res = s_cmd->tokens;
		while (get_next_line(fd, &line))
			res = ft_realloc(res, line);
	}
	int j = 0;
	while (res[j])
		printf("%s\n", res[j++]);
	return (res);
}

void	exec_full(size_t index, char **args)
{
	int		p1[2]; // p1[0] - read || p[1] - write
	pid_t	pid;

	pid = fork();
	pipe(p1);
	if (pid == 0)
	{
		// Child process
		int	redir_out;
		
		printf("Child Process %ld : Process is starting\n", index + 1);
		close(p1[0]);
		printf("Child Process %ld : Closing reading pipe (obvious)\n", index + 1);
		redir_out = apply_outredir(g_fcmd->s_cmd[index]);
		// redir_out == 1 if there is NO output redirection set (keep pointing to STDOUT)
		// redir_out == ? if there IS an output redirection set
		printf("Child Process %ld : Output redirection set to %d\n", index + 1, redir_out);
		if (redir_out == 1 && index != g_fcmd->nb_scmd - 1)
		{
			// In this case, no output redirection are set but there is an other command
			// waiting for that output.
			// So we need to send the output to the main process using the pipe.
			printf("Child Process %ld : STDOUT now goes to the pipe\n", index + 1);
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
			printf("Child Process %ld : STDOUT now goes to the specified redirection\n", index + 1);
			dup2(redir_out, STDOUT_FILENO);
			// Now the output will be the one specified by redir_out.
			if (redir_out != 1)
				close(redir_out);
				// If redir_out is 1, it is a bad idea to close STDOUT.
		}
		close(p1[1]);
		//printf("Child Process : Closing wrting pipe\n");
		is_builtin(g_fcmd->s_cmd[index], args);
		exit(0);
	}
	else
	{
		waitpid(g_fcmd->child_id, NULL, 0);
		g_fcmd->child_id = -1;
		close(fd[1]);
		// close(fd_out);
	}
	else
	{
		printf("Parent Process %ld : Process is starting\n", index + 1);
		close(p1[1]);
		printf("Parent Process %ld : Closing writing pipe (obvious)\n", index + 1);
		wait(NULL);
		printf("Parent Process %ld : Waiting for child execution\n", index + 1);
		if (index != g_fcmd->nb_scmd - 1)
		{
			// If this is not the last command, we need to set args to the args of the next
			// command and execute this function again.
			args = find_in_tab(g_fcmd->s_cmd[index + 1], p1[0]);
			printf("Parent Process %ld : Data traited from the pipe\n", index + 1);
			close(p1[0]);
			printf("Parent Process %ld : Closing reading pipe\n", index + 1);
			close(p1[1]);
			printf("Parent Process %ld : Launching next recursion\n", index + 1);
			exec_full(index + 1, args);
		}
		printf("Parent Process %ld : End of execution\n", index + 1);
	}
	return ;
}
