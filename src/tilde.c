/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.42.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 21:06:40 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/04 18:05:47 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*one_tilde(char *str)
{
	size_t	i;
	size_t	t;
	char	*res;

	i = 0;
	t = 0;
	res = str;
	while (str[i])
	{
		if (str[i] == '~')
			t++;
		i++;
	}
	if (t == 1)
		res = tilde(str);
	return (res);
}

char	*tilde(char *str)
{
	char	*home;
	char	*temp;
	char	*temp2;
	size_t	i;

	home = getenv("HOME");
	i = 0;
	while (str[i])
	{
		if (str[i] == '~')
		{
			temp = ft_substr(str, 0, i);
			temp2 = ft_strcat(temp, home);
			free(temp);
			temp = ft_substr(str, i + 1, ft_strlen(str));
			temp2 = ft_strcat(temp2, temp);
			free(temp);
			return (temp2);
		}
		i++;
	}
	return (str);
}
