/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:02:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/22 15:32:24 by npinheir         ###   ########.fr       */
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
		if (take_input())
		{
			init_full_cmd(g_fcmd->f_cmd);
			env_variables();
			parse_redir();
			parse_cmd();
			__exec_full(0, g_fcmd->s_cmd[0]->tokens, 0);
		}
		clear_all();
	}
	return (0);
}
