/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.42.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 21:06:40 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/06 17:12:02 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*one_tilde(char *str)
{
	size_t	i;
	char	*res;

	i = 0;
	res = str;
	while (res[i])
	{
		if (res[i] == '~' && ft_isspace(res[i - 1]) && (ft_isspace(res[i + 1])
				|| res[i + 1] == '/' || !res[i + 1]))
		{
			res = tilde(res, i);
			i = 0;
			continue ;
		}
		i++;
	}
	return (res);
}

char	*tilde(char *str, size_t i)
{
	char	*home;
	char	*temp;
	char	*temp2;

	home = getenv("HOME");
	temp = ft_substr(str, 0, i);
	temp2 = ft_strcat(temp, home);
	free(temp);
	temp = ft_substr(str, i + 1, ft_strlen(str));
	home = ft_strcat(temp2, temp);
	free(temp);
	free(temp2);
	free(str);
	return (home);
}
