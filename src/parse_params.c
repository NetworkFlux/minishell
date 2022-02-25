/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:45:23 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/24 18:34:03 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	find_param_end(char *input, size_t position)
{
	while (input && input[position])
	{
		if (is_delimiter(input[position])
			|| ft_isspace(input[position]))
			return (position);
		position++;
	}
	if (input[position] == '\0')
		return (position);
	return (0);
}

int	parse_param(s_cmd_t *s_cmd, size_t *start, int *is_command, size_t *i)
{
	size_t	end;
	char	*token;

	end = find_param_end(s_cmd->s_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		token = tokenize(s_cmd->s_cmd, *start, end);
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
