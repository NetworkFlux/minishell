/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:05:54 by npinheir          #+#    #+#             */
/*   Updated: 2021/11/05 10:07:40 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	this function returns the amount of digits in the integer n.	*/

int	ft_intlen(int n)
{
	int	res;

	if (n <= 0)
		res = 1;
	else
		res = 0;
	while (n != 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}
