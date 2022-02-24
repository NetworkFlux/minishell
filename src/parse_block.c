/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:44:22 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/24 10:56:54 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check block start ' " (
int	is_block_start(char c)
{
	if (
		(unsigned char) c == '\''
		|| (unsigned char) c == '"'
		|| (unsigned char) c == '(')
		return (1);
	return (0);
}

// returns 0 when no blockend is not found / end position on success
size_t	find_block_end(char *input, size_t position)
{
	char	target;

	target = input[position];
	if (input[position] == '(')
		target = ')';
	position++;
	while (input && input[position])
	{
		if (input[position] == target)
			return (position);
		position++;
	}
	return (0);
}

int	parse_block(f_cmd_t *f_cmd, size_t *start, int *is_command)
{
	size_t	end;

	end = find_block_end(f_cmd->f_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		f_cmd->tokens[f_cmd->itoken] = tokenize(f_cmd->f_cmd, *start + 1, end);
		if (!f_cmd->tokens[f_cmd->itoken])
			return (0);
		if (*is_command)
			printf("is_command ");
		printf("block: %s\n", f_cmd->tokens[f_cmd->itoken]);
		*is_command = 0;
		f_cmd->itoken++;
		end++;
	}
	*start = end;
	return (1);
}
