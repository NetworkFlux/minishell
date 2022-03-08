/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:39:19 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/07 09:33:07 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_option_ok(char *str)
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

// Runs the echo command
void	buildins_echo(t_scmd *scmd, int fd_out)
{
	size_t	i;

	i = 0;
	if (scmd->tokens 
		&& scmd->tokens[0]
		&& scmd->tokens[0]->token
		&& scmd->tokens[0]->token[0])
	{
		if (scmd->tokens[0]->token[0] == '-')
			i++;
		ft_putstr_fd(scmd->tokens[i]->token, fd_out);
		while (++i < scmd->ntokens)
		{
			ft_putchar_fd(' ', fd_out);
			ft_putstr_fd(scmd->tokens[i]->token, fd_out);
		}
		if (!is_option_ok(scmd->tokens[0]->token))
			ft_putchar_fd('\n', fd_out);
	}
	else
		ft_putchar_fd('\n', fd_out);
	if (fd_out > 2)
		close(fd_out);
}
