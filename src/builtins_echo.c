/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:39:19 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/22 15:26:07 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option_ok(char *str)
{
	size_t	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] == 'n')
				return (1);
			i++;
		}
	}
	return (0);
}

// called from child process
void	output_echo(t_scmd *scmd)
{
	size_t	i;

	i = 1;
	if (redir_files_ok(scmd) < 0)
		exit(1);
	if (scmd->tokens && scmd->tokens[1])
	{
		if (scmd->tokens[1][0] == '-')
			i++;
		ft_putstr_fd(scmd->tokens[i], 1);
		while (++i < scmd->ntokens)
		{
			ft_putchar_fd(' ', 1);
			ft_putstr_fd(scmd->tokens[i], 1);
		}
		if (!is_option_ok(scmd->tokens[1]))
			ft_putchar_fd('\n', 1);
	}
	else
		ft_putchar_fd('\n', 1);
	exit(0);
}

// Runs the echo command
int		buildins_echo(t_scmd *scmd, int readpipe)
{
	return (pipeline(scmd, &output_echo, readpipe));
}
