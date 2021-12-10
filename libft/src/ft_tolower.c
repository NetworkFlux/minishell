/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 16:33:19 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:01:45 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	This function converts an upper-case letter to
	the corresponding lower-case letter.	*/

int	ft_tolower(int c)
{
	if (!c)
		return (0);
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
