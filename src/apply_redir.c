/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:50 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/08 10:59:04 by npinheir         ###   ########.fr       */
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
			return; // gerer l'erreur
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
		temp = open(scmd->redir->outout_args[i++], O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (!temp)
			return; // gerer l'erreur
		close(temp);
	}
}

// creates all de desired files and closes them but leaves the last one open
int		apply_outredir(t_scmd *scmd)
{
	int		fd;
	int		temp;

	temp = 1;
	if (!scmd->redir->out || scmd->redir->outout)
		return (1);
	create_redir_file_s(scmd);
	temp = open(scmd->redir->out_args[scmd->redir->out - 1], O_CREAT | O_WRONLY, 0777);
	if (!temp)
		return (1); // gere l'erreur
	fd = temp;
	create_redir_file_d(scmd);
	temp = open(scmd->redir->outout_args[scmd->redir->outout - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (!temp)
		return (1); // gere l'erreur
	if (scmd->redir->last_out == 2)
	{
		close(fd);
		fd = temp;
	}
	else
		close(temp);
	return (fd);
}