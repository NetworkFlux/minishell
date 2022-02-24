/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:41:03 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/24 10:50:46 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_commands(f_cmd_t *f_cmd, int *is_command, int end_value)
{
	if (*is_command)
		f_cmd->ncmd++;
	*is_command = end_value;
}

// before parsing, count input's tokens
int	count_input(f_cmd_t *f_cmd, size_t start)
{
	int	is_command;

	is_command = 1;
	while (start < ft_strlen(f_cmd->f_cmd))
	{
		while (f_cmd->f_cmd && ft_isspace(f_cmd->f_cmd[start]))
			start++;
		if (is_block_start(f_cmd->f_cmd[start]))
		{
			start = find_block_end(f_cmd->f_cmd, start);
			if (start++ == 0)
				return (0);
			count_commands(f_cmd, &is_command, 0);
		}
		else if (is_delimiter(f_cmd->f_cmd[start]))
		{
			start = find_delimiter_end(f_cmd->f_cmd, start);
			if (start == 0)
				return (0);
			count_commands(f_cmd, &is_command, 1);
		}
		else
		{
			start = find_param_end(f_cmd->f_cmd, start);
			if (start++ == 0)
				return (0);
			count_commands(f_cmd, &is_command, 0);
		}
		f_cmd->ntokens++;
	}
	return (1);
}
