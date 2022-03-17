/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:32:43 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/17 17:24:23 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear_array(char **array, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free (array[i]);
		i++;
	}
	free(array);
	return (1);
}
