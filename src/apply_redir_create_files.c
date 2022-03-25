/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_create_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:00:47 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/25 11:26:19 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_redir_file_s(t_scmd *scmd)
{
	size_t	i;
	int		temp;

	temp = 1;
	i = 0;
	while (scmd->redir->out_args[i] && i < scmd->redir->out - 1)
	{
		temp = open(scmd->redir->out_args[i++], O_CREAT | O_WRONLY, 0777);
		if (!temp)
			clear_all();
		close(temp);
	}
}

void	create_redir_file_d(t_scmd *scmd)
{
	size_t	i;
	int		temp;

	temp = 1;
	i = 0;
	while (scmd->redir->outout_args[i] && i < scmd->redir->out - 1)
	{
		temp = open(scmd->redir->outout_args[i++], \
			O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (!temp)
			clear_all();
		close(temp);
	}
}
