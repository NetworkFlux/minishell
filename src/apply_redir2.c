/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:54:59 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/05 20:22:04 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_outredir2(t_scmd *scmd, int fd1)
{
	int		fd;

	fd = 1;
	if (!scmd->redir->last_out)
		return (1);
	create_redir_file_s(scmd);
	if (scmd->redir->last_out == 2)
	{
		fd = open(scmd->redir->outout_args[scmd->redir->outout - 1], \
			O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (!fd)
			clear_all();
		close(fd1);
		fd1 = fd;
	}
	return (fd1);
}
