/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:45:23 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/24 17:07:44 by fcaquard         ###   ########.fr       */
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

int	parse_param(s_cmd_t *s_cmd, size_t *start, int *is_command)
{
	size_t	end;

	end = find_param_end(s_cmd->s_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		s_cmd->tokens[s_cmd->itoken] = tokenize(s_cmd->s_cmd, *start, end);
		if (!s_cmd->tokens[s_cmd->itoken])
			return (0);
		if (*is_command)
			printf("is_command ");
		printf("param: %s\n", s_cmd->tokens[s_cmd->itoken]);
		*is_command = 0;
		s_cmd->itoken++;
		end++;
	}
	*start = end;
	return (1);
}
