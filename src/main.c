/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:02:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/19 13:52:41 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// concats previous input with new input
static char	*total_input(char *cmd, char *tmp)
{
	char	*total;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	total = malloc(sizeof(char) * (ft_strlen(cmd) + ft_strlen(tmp)) + 1);
	if (!total)
	{
		free(cmd);
		free(tmp);
		error_malloc(1);
	}
	while (cmd && cmd[i])
		total[j++] = cmd[i++];
	i = 0;
	while (tmp && tmp[i])
		total[j++] = tmp[i++];
	total[(ft_strlen(cmd) + ft_strlen(tmp))] = '\0';
	free (cmd);
	free (tmp);
	return (total);
}

char	*take_input(void)
{
	char	*cmd;
	char	*tmp;

	cmd = readline("minishell => ");
	if (!cmd)
		clear_exit();
	if (!strlen(cmd))
	{
		free(cmd);
		take_input();
	}
	else
	{
		while (cmd && is_input_incomplete(cmd))
		{
			tmp = readline("> ");
			cmd = total_input(cmd, tmp);
		}
		if (!cmd)
			error_malloc(1);
		add_history(cmd);
	}
	g_fcmd->f_cmd = cmd;
	return (cmd);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Usage : ./minishell", 1);
		return (1);
	}
	init_signals();
	g_fcmd = malloc(sizeof(t_fcmd));
	if (!g_fcmd)
		error_malloc(1);
	g_fcmd->child_id = -1;
	g_fcmd->env = NULL;
	g_fcmd->exitcode = 0;
	g_fcmd->envp = create_env(envp);
	while (1)
	{
		take_input();
		init_full_cmd(g_fcmd->f_cmd);
		env_variables();
		parse_redir();
		parse_cmd();
		exec_full(0, g_fcmd->s_cmd[0]->tokens);
		clear_all();
		printf("-------------\n"); // remove
	}
	return (0);
}
