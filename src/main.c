/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:02:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/19 18:28:44 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Usage : ./minishell", 1);
		return (1);
	}
	init_signals();
	init_global(envp);
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
