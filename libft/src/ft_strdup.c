/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:35:33 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:01:16 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function allocates sufficient memory
	for a copy of the string s1, does the copy,
	and returns a pointer to it.	*/

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	i;

	if (!s1)
		return (NULL);
	res = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i] = '\0';
	return (res);
}
