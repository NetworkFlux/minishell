/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:02:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/03 15:57:32 by fcaquard         ###   ########.fr       */
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
		return (NULL);
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
	if (!ft_strlen(cmd))
	{
		free(cmd);
		cmd = take_input();
	}
	else
	{
		while (cmd && is_input_incomplete(cmd))
		{
			tmp = readline("> ");
			cmd = total_input(cmd, tmp);
		}
		if (!cmd)
			return (NULL);
		add_history(cmd);
	}
	return (cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Usage : ./minishell", 1);
		return (1);
	}
	init_signals();
	while (1)
	{
		cmd = take_input();
		if (!cmd)
			return (1);
		printf("<main> init_full_cmd\n");
		init_full_cmd(cmd);
		g_fcmd->envp = envp;
		printf("<main> parse_redir\n");
		parse_redir();
		printf("<main> env_variables\n");
		env_variables();
		printf("<main> remove_quotes\n");
		remove_quotes();
		printf("<main> get_exec\n");
		get_exec();
		printf("<main> parse_cmd\n");
		if (!parse_cmd())
			return (1);
		// exec();
		clear_all();
	}
	return (0);
}
