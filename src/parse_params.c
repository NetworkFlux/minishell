/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:45:23 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/02 20:55:32 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	is_delimiter(int c)
{
	if (c == '|')
		return (1);
	return (0);
}*/

size_t	find_param_end(char *input, size_t position)
{
	while (input && input[position])
	{
		if (is_block_start(input[position]))
			position = find_block_end(input, position);
		else if (ft_isspace(input[position]))
				return (position);
		else
			position++;
	}
	if (input[position] == '\0')
		return (position);
	return (0);
}

/**	Looks for the end of a parameter
	(anything that isn't a space, a blockstart
	or a delimiter) then tokenizes it */
int	parse_param(t_scmd *s_cmd, size_t *start, size_t *i)
{
	size_t	end;
	char	*token;

	end = find_param_end(s_cmd->instructions, *start);
	if (end == 0)
	{
		printf("error\n");
		return (0);
	}
	else
	{
		token = tokenize(s_cmd->instructions, *start, end);
		if (!token)
			return (0);
		s_cmd->tokens[(*i)++]->token = token;
		printf("token: %s\n", token);
	}
	*start = end;
	printf("%c\n", s_cmd->instructions[*start]);
	return (1);
}
