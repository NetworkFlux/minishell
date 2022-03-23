/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:42:43 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/23 21:25:50 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks if the ' " are closed
int	is_input_incomplete(char *input)
{
	size_t	i;
	char	c;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			c = input[i++];
			while (input && input[i] && input[i] != c)
				i++;
			if (!input || input[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}
