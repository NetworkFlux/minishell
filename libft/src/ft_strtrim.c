/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 08:03:12 by npinheir          #+#    #+#             */
/*   Updated: 2021/08/23 08:10:25 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function allocates and returns a copy
	of ’s1’ with the characters specified in
	’set’ removed from the beginning and the
	end of the string.	*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size_s;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size_s = ft_strlen(s1);
	while (size_s && ft_strchr(set, s1[size_s]))
		size_s--;
	res = ft_substr((char *)s1, 0, size_s + 1);
	return (res);
}
