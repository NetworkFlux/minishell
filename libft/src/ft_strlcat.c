/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 16:16:25 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:01:26 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function appends string src to the end of dst.
	It will append at most dstsize - strlen(dst) - 1
	characters. It will then NUL-terminate, unless
	dstsize is 0 or the original dst string was longer
	than dstsize.	*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	res;

	res = ft_strlen(src);
	i = ft_strlen(dst);
	j = 0;
	if (!dst || !src)
		return (0);
	if (dstsize <= i)
		res += dstsize;
	else
		res += i;
	while (src[j] && (i + 1) < dstsize)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (res);
}
