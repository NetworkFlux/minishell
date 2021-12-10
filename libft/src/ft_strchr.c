/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 16:36:41 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:01:11 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function locates the first occurrence of c
	(converted to a char) in the string pointed to by s.
	The terminating null character is considered to be
	part of the string; therefore if c is `\0', the functions
	locate the terminating `\0'.	*/

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c && (*str + 256) != c)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return (str);
}
