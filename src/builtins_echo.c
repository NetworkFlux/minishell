/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:39:19 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/07 11:53:30 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Runs the echo command
void	buildins_echo(t_scmd *scmd, int fd_out)
{
	size_t	i;

	i = 1;
	if (scmd->tokens && scmd->tokens[1])
	{
		if (scmd->tokens[1][0] == '-')
			i++;
		ft_putstr_fd(scmd->tokens[i], fd_out);
		while (++i < scmd->ntokens)
		{
			ft_putchar_fd(' ', fd_out);
			ft_putstr_fd(scmd->tokens[i], fd_out);
		}
		if (scmd->tokens[1][0] == '-')
			ft_putchar_fd('%', fd_out);
		ft_putchar_fd('\n', fd_out);
	}
	else
		ft_putchar_fd('\n', fd_out);
	if (fd_out > 2)
		close(fd_out);
}
