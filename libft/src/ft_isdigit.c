/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 00:01:56 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:00:07 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function returns 1 if the integer input
	corresponds to a digit character.
	Returns 0 otherwise.	*/

int	ft_isdigit(int c)
{
	if (!c)
		return (0);
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
