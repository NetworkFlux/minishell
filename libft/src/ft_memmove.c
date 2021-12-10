/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:15:09 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:00:57 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function copies len bytes from string
	src to string dst.The The copy is always
	done in a non-destructive manner.	*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*res;

	if ((!dst && !src))
		return (NULL);
	res = dst;
	if (dst >= src)
	{
		while (len--)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (res);
}
