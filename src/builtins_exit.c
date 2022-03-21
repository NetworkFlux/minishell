/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:16:55 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/21 14:46:11 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **builtins_exit(t_scmd *scmd, char **args)
{
	(void)args;
	(void)scmd;
	clear_exit();
	return (args);
}
