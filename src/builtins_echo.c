/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:39:19 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/21 16:32:53 by fcaquard         ###   ########.fr       */
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
void	output_echo(t_scmd *scmd, char **args)
{
	(void)args;
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
		if (!is_option_ok(scmd->tokens[0]))
			ft_putchar_fd('\n', 1);
	}
	else
		ft_putchar_fd('\n', 1);
	exit(0);
}

// Runs the echo command
char	**buildins_echo(t_scmd *scmd, char **args)
{
	args = pipeline(scmd, args, &output_echo);
	return (args);
}
