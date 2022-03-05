/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:50:19 by fcaquard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/05 15:13:06 by npinheir         ###   ########.fr       */
=======
/*   Updated: 2022/03/05 11:53:06 by fcaquard         ###   ########.fr       */
>>>>>>> 457aecb1078473f5c28cb21c29bb7315e408256c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* prints the name of the current directory */
// Probably not a good way to output it
// Should test if it works alongside with `cd`
void	buildins_pwd(t_scmd *scmd, int fd_out)
{
	char	*res;

	res = NULL;
	if (scmd->ntokens != 0)
	{
		printf("<pwd> Too many arguments\n");
		return ;
	}
<<<<<<< HEAD
	ft_putendl_fd(getcwd(res, sizeof(res)), fd_out);
	if (fd_out > 2)
		close(fd_out);
=======
	printf("%s\n", getcwd(res, ft_strlen(res)));
>>>>>>> 457aecb1078473f5c28cb21c29bb7315e408256c
	return ;
}