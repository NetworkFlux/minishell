/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:51:04 by npinheir          #+#    #+#             */
/*   Updated: 2021/08/22 16:30:44 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function locates the last occurrence of c
	(converted to a char) in the string pointed to by s.
	The terminating null character is considered to be
	part of the string; therefore if c is `\0', the functions
	locate the terminating `\0'.	*/

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = NULL;
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == (char)c)
			str = (char *)s;
		s++;
	}
	return (str);
}
