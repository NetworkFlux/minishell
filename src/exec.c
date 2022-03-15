/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:06:46 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/15 19:23:20 by fcaquard         ###   ########.fr       */
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
