/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:41:03 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/26 17:41:23 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_commands(t_scmd *s_cmd, int *is_command, int end_value)
{
	if (!*is_command)
		s_cmd->ntokens++;
	*is_command = end_value;
}

// before parsing, count input's tokens
int	count_input(t_scmd *s_cmd, size_t start)
{
	int	is_command;

	is_command = 1;
	while (start < ft_strlen(s_cmd->s_cmd))
	{
		while (s_cmd->s_cmd[start] && ft_isspace(s_cmd->s_cmd[start]))
			start++;
		if (s_cmd->s_cmd[start])
		{
			if (is_block_start(s_cmd->s_cmd[start]))
			{
				start = find_block_end(s_cmd->s_cmd, start);
				if (start++ == 0)
					return (0);
			}
			else
			{
				start = find_param_end(s_cmd->s_cmd, start);
				if (start++ == 0)
					return (0);
			}
			count_commands(s_cmd, &is_command, 0);
		}
	}
	return (1);
}
