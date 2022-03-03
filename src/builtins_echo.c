/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:39:19 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/02 21:05:09 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	buildins_echo(t_scmd *scmd)
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
		ft_putstr_fd(scmd->tokens[i]->token, 1);
		while (++i < scmd->ntokens)
		{
			ft_putchar_fd(' ', 1);
			ft_putstr_fd(scmd->tokens[i]->token, 1);
		}
		if (scmd->tokens[0]->token[0] == '-')
			ft_putchar_fd('%', 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		ft_putchar_fd('\n', 1);
	}
}
