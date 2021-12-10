/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 08:23:54 by npinheir          #+#    #+#             */
/*   Updated: 2021/11/05 10:34:03 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function allocates and returns a string
	representing the integer received as an argument.
	Negative numbers must be handled.	*/

static int	ft_unsignedintlen(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

unsigned int	neg_check(int n, unsigned int *len)
{
	unsigned int	res;

	if (n < 0)
	{
		res = -n;
		*len = 1;
	}
	else
		res = n;
	return (res);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;
	unsigned int	nb;
	unsigned int	i;

	len = 0;
	nb = neg_check(n, &len);
	len += ft_unsignedintlen(nb);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	i = 0;
	if (n < 0)
		res[i] = '-';
	i = len - 1;
	while (nb >= 10)
	{
		res[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	res[i] = (nb % 10) + '0';
	res[len] = '\0';
	return (res);
}
