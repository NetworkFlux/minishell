/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:39:19 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/23 12:05:36 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option_ok(char *str, int *newline)
{
	size_t	i;

	i = 1;
	if (str && str[0] != '-')
		return (0);
	while (str && str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	*newline = 0;
	return (1);
}

// called from child process
void	output_echo(t_scmd *scmd)
{
	size_t	i;
	int		option_flag;
	int		newline;

	newline = 1;
	option_flag = 1;
	i = 1;
	if (redir_files_ok(scmd) < 0)
		exit(1);
	while (scmd->tokens && i < scmd->ntokens && scmd->tokens[i])
	{
		if (option_flag)
			option_flag = is_option_ok(scmd->tokens[i], &newline);
		if (!option_flag)
		{
			ft_putstr_fd(scmd->tokens[i], 1);
			if (i + 1 < scmd->ntokens)
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	exit(0);
}

// Runs the echo command
int	buildins_echo(t_scmd *scmd, int readpipe)
{
	return (pipeline(scmd, &output_echo, readpipe));
}
