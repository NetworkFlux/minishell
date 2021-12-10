/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 16:28:17 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:01:48 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function converts a lower-case letter to
	the corresponding upper-case letter.	*/

int	ft_toupper(int c)
{
	if (!c)
		return (0);
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}
