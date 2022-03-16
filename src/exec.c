/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:06:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/16 19:18:13 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concat(char *first, char *append)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new = malloc (sizeof(char) * ft_strlen(first) + ft_strlen(append) + 1);
	if (!new)
		error_malloc();
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
}

/*	if exec isn't a builtin execute it 
	using fork and execve */
void	exec(t_scmd *scmd, t_env *env)
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


char	**find_in_tab(t_scmd *s_cmd, int fd)
{
	char	**res;
	char	*line;

	line = NULL;
	if (s_cmd->redir->in || s_cmd->redir->inin)
		res = apply_inredir(s_cmd);
	else
	{
		res = malloc(sizeof(char *) * 2);
		res[0] = s_cmd->tokens[0];
		res[1] = NULL;
		while (get_next_line(fd, &line))
			res = ft_realloc(res, line);
		close(fd);
	}
	int j = 0;
	while (res[j])
		printf("%s\n", res[j++]);
	return (res);
}

void	exec_full(size_t index, char **args)
{
	int	fd[2];
	int	fd_out = 0;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		fd_out = apply_outredir(g_fcmd->s_cmd[index]);
		if (fd_out == 1 && index != g_fcmd->nb_scmd - 1)
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(fd_out, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		is_builtin(g_fcmd->s_cmd[index], args);
	}
	waitpid(pid, NULL, 0);
	close(fd[1]);
	close(fd_out);
	if (index != g_fcmd->nb_scmd - 1)
		exec_full(index + 1, find_in_tab(g_fcmd->s_cmd[index + 1], fd[0]));
}
