/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 00:07:18 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:00:00 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function returns 1 if the integer input
	corresponds to an alphabetical character or.
	a digit character. Returns 0 otherwise.	*/

int	ft_isalnum(int c)
{
	if (!c)
		return (0);
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}
