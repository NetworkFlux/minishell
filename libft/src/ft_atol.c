/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:17:49 by npinheir          #+#    #+#             */
/*   Updated: 2021/12/06 14:03:25 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	skipuselesschar(const char *str)
{
	long	i;

	i = 0;
	while (str[i] == '\t'
	|| str[i] == '\n'
	|| str[i] == '\v'
	|| str[i] == '\r'
	|| str[i] == '\f'
	|| str[i] == ' ')
		++i;
	return (i);
}

long		ft_atol(const char *str)
{
	long		result;
	long		isneg;
	long		i;

	result = 0;
	i = skipuselesschar(str);
	isneg = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		isneg = (str[i] == '-' ? 1 : 0);
		++i;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - 48;
		++i;
	}
	return (isneg == 1 ? result *= -1 : result);
}