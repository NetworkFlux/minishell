/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_create_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:00:47 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/31 17:51:35 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_redir_file_s(t_scmd *scmd)
{
	size_t	i;
	int		temp;

	temp = 1;
	i = 0;
	while (scmd->redir->out > 0
		&& i < scmd->redir->out - 1
		&& scmd->redir->out_args
		&& scmd->redir->out_args[i])
	{
		temp = open(scmd->redir->out_args[i], O_CREAT | O_WRONLY, 0664);
		if (!temp)
			clear_all();
		close(temp);
		i++;
	}
}

void	create_redir_file_d(t_scmd *scmd)
{
	size_t	i;
	int		temp;

	temp = 1;
	i = 0;
	while (scmd->redir->outout > 0
		&& i < scmd->redir->outout - 1
		&& scmd->redir->outout_args
		&& scmd->redir->outout_args[i])
	{
		temp = open(scmd->redir->outout_args[i], \
			O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (!temp)
			clear_all();
		close(temp);
		i++;
	}
}
