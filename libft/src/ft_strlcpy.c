/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:19:10 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:01:29 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function copies up to dstsize - 1 characters
	from the string src to dst, NUL-terminating the
	result if dstsize is not 0.	*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	if (!dstsize)
		return (ft_strlen(src));
	i = -1;
	while (src[++i] && dstsize-- > 1 )
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}
