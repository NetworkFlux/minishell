/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:44:22 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/24 18:33:56 by fcaquard         ###   ########.fr       */
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

int	parse_block(s_cmd_t *s_cmd, size_t *start, int *is_command, size_t *i)
{
	size_t	end;
	char	*token;

	end = find_block_end(s_cmd->s_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		// start + 1 so we remove the quotes 
		token = tokenize(s_cmd->s_cmd, *start + 1, end);
		if (!token)
			return (0);
		if (*is_command)
			s_cmd->exec = token;
		else
		{
			s_cmd->tokens[*i] = token;
			(*i)++;
		}
		*is_command = 0;
		end++;
	}
	*start = end;
	return (1);
}
