/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:08:31 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/03 19:27:48 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	get_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i != 0)
			return (i);
		else if (str[i] == '=')
			return (1);
		i++;
	}
	return (-1);
}

int	export_args(char *str)
{
	size_t	i;
	int		equal;
	char	*temp;

	i = 1;
	equal = 0;
	equal = get_equal(str);
	if (equal == -1)
		return (2);
	temp = ft_substr(str, 0, equal);
	if (str_alpha(temp))
	{
		free(temp);
		return (1);
	}
	free(temp);
	i++;
	return (0);
}
