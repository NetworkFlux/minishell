/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:44:58 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/21 16:49:25 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *str1, char *str2)
{
	size_t	len;
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str1 || !str2)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	while (str2[j])
		res[i++] = str2[j++];
	res[i] = '\0';
	return (res);
}