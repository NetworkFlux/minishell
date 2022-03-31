/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_create_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.42.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:00:47 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/28 12:27:19 by npinheir         ###   ########.fr       */
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
		temp = open(scmd->redir->out_args[i], O_CREAT | O_WRONLY, 0777);
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
			O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (!temp)
			clear_all();
		close(temp);
		i++;
	}
}
