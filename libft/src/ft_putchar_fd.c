/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 18:35:13 by npinheir          #+#    #+#             */
/*   Updated: 2021/08/26 18:36:27 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function outputs the character ’c’
	to the given file descriptor.	*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
