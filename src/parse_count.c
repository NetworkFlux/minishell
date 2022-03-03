/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:41:03 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/02 20:55:19 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// before parsing, in order to malloc our variables
// count how many tokens we will have (exec not included)
int	count_input(t_scmd *s_cmd, size_t start)
{
	while (s_cmd->instructions[start])
	{
		while (s_cmd->instructions[start] && ft_isspace(s_cmd->instructions[start]))
			start++;
		printf("start: %ld\n", start);
		if (s_cmd->instructions[start])
		{
			// if (is_block_start(s_cmd->instructions[start]))
			// {
			// 	start = find_block_end(s_cmd->instructions, start);
			// 		return (0);
			// }
			// else
			// {
			// 	printf("end: %ld\n", start);
			// }
			start = find_param_end(s_cmd->instructions, start);
			if (start == 0)
				return (0);
		}
		start++;
		s_cmd->ntokens++;
	}
	return (1);
}
