/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:45:23 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/24 10:54:49 by fcaquard         ###   ########.fr       */
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

int	parse_param(f_cmd_t *f_cmd, size_t *start, int *is_command)
{
	size_t	end;

	end = find_param_end(f_cmd->f_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		f_cmd->tokens[f_cmd->itoken] = tokenize(f_cmd->f_cmd, *start, end);
		if (!f_cmd->tokens[f_cmd->itoken])
			return (0);
		if (*is_command)
			printf("is_command ");
		printf("param: %s\n", f_cmd->tokens[f_cmd->itoken]);
		*is_command = 0;
		f_cmd->itoken++;
		end++;
	}
	*start = end;
	return (1);
}
