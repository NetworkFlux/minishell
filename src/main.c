/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:02:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/23 16:47:56 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// concats previous input with new input
static	char *total_input(char *cmd, char *completion)
{
	char *total;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	total = malloc(sizeof(char) * (ft_strlen(cmd) + ft_strlen(completion)) + 1);
	if (!total)
	{
		free(cmd);
		free(completion);
		return (NULL);
	}
	while (cmd && cmd[i])
		total[j++] = cmd[i++];
	i = 0;
	while (completion && completion[i])
		total[j++] = completion[i++]; 
	total[(ft_strlen(cmd) + ft_strlen(completion))] = '\0';
	return (total);
}

char	*take_input(void)
{
	char	*cmd;
	char	*completion;

	cmd = readline("minishell => ");
	if (!ft_strlen(cmd))
		cmd = take_input();
	else
	{
		while (cmd && is_input_incomplete(cmd))
		{
			completion = readline("> ");
			cmd = total_input(cmd, completion);
		}
		if (!cmd)
			return (NULL);
		add_history(cmd);
	}
	return (cmd);
}

int	main(int argc, char **argv)
{
	(void)argv;
	f_cmd_t	*f_cmd;
	char	*cmd;

	if (argc != 1)
	{
		ft_putendl_fd("Usage : ./minishell", 1);
		return (1);
	}
	while (1)
	{
		cmd = take_input();
		if (!cmd)
			return (1);
		f_cmd = init_full_cmd(cmd);
		// parse(f_cmd);
		ft_strtok(f_cmd->f_cmd, 0, f_cmd);
	}
	return (0);
}
