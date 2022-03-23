/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:46:28 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/23 12:17:30 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prints / clear all / exit(0)
int	error_malloc(int n)
{
	(void)n;
	perr(12, "malloc");
	clear_exit(n);
	return (0);
}

void	perr(int code, char *str)
{
	errno = code;
	perror(str);
}
