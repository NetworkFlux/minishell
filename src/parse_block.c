/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:44:22 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/26 17:24:07 by fcaquard         ###   ########.fr       */
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

static void	block_type(char c, t_token *token)
{
	if ((unsigned char) c == '\'')
		token->type = singleq;
	else if ((unsigned char) c == '"')
		token->type = doubleq;
	else if ((unsigned char) c == '(')
		token->type = parenthesis;
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

// line 67: *start + 1 so we remove the starting quote
// line 75: end++ so we start after the last quote
int	parse_block(t_scmd *s_cmd, size_t *start, int *is_command, size_t *i)
{
	size_t	end;
	char	*token;

	end = find_block_end(s_cmd->s_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		block_type(s_cmd->s_cmd[*start], s_cmd->tokens[*i]);
		token = tokenize(s_cmd->s_cmd, *start + 1, end);
		if (!token)
			return (0);
		if (*is_command)
			s_cmd->exec = token;
		else
			s_cmd->tokens[(*i)++]->token = token;
		*is_command = 0;
		end++;
	}
	*start = end;
	return (1);
}
