/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:42:43 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/24 10:50:22 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks if the ' " ( are closed
int	is_input_incomplete(char *input)
{
	size_t	i;
	size_t	res;

	i = 0;
	while (input && input[i])
	{
		if (is_block_start(input[i]))
		{	
			res = find_block_end(input, i);
			if (res == 0)
				return (1);
			i = res;
		}
		i++;
	}
	return (0);
}
