/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:02:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/15 06:52:34 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_input(void)
{
	char	*cmd;

	cmd = readline("minishell => ");
	if (!ft_strlen(cmd))
		cmd = take_input();
	else
		add_history(cmd);
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
		f_cmd = init_full_cmd(cmd);
		parse(f_cmd);
	}
	return (0);
}
