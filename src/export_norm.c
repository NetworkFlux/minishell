/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:36:23 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/03 19:36:23 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_norm2(char **array)
{
	if (!insert_update_env(array[0], array[1]))
	{
		clear_array(array, ft_arrlen(array));
		error_malloc(1);
	}
	clear_array(array, ft_arrlen(array));
}
