/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 16:42:34 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 11:59:52 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function writes n zeroed bytes
	to the string s. If n is zero, this
	function does nothing.*/

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!s || !n)
		return ;
	i = 0;
	while (i < n)
		((char *)s)[i++] = 0;
}
