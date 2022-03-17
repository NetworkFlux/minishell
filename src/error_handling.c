/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:46:28 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/17 17:22:13 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prints / clear all / exit(0)
int	error_malloc(int n)
{
	(void)n;
	printf("Memory allocation failed.\n");
	clear_exit();
	return (0);
}
