/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:43:18 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/24 14:18:13 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// commented redirection delimiters
int	is_delimiter(int c)
{
	// if (c == '|' || c == '>' || c == '<')
	if (c == '|')
		return (1);
	return (0);
}

// returns 0 when end delimiter is not found / end position on success
// commented redirection delimiters
size_t	find_delimiter_end(char *input, size_t start)
{
	size_t	len;

	len = 0;
	if ((unsigned char) input[start] == '|')
	{
		while (input[start] && input[start] == '|')
		{
			start++;
			len++;
		}
		if (len < 3)
			return (start);
		printf("bash: syntax error near unexpected token `|'\n");
	}
	// else if ((unsigned char) input[start] == '>')
	// {
	// 	while (input[start] && input[start] == '>')
	// 	{
	// 		start++;
	// 		len++;
	// 	}
	// 	if (len < 3)
	// 		return (start);
	// 	printf("bash: syntax error near unexpected token `>'\n");
	// }
	// else if ((unsigned char) input[start] == '<')
	// {
	// 	while (input[start] && input[start] == '<')
	// 	{
	// 		start++;
	// 		len++;
	// 	}
	// 	if (len < 4)
	// 		return (start);
	// 	printf("bash: syntax error near unexpected token `<'\n");
	// }
	return (0);
}

int	parse_delimiter(f_cmd_t *f_cmd, size_t *start, int *is_command)
{
	size_t	end;

	end = find_delimiter_end(f_cmd->f_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		f_cmd->tokens[f_cmd->itoken] = tokenize(f_cmd->f_cmd, *start, end);
		if (!f_cmd->tokens[f_cmd->itoken])
			return (0);
		printf("delimiter: %s\n", f_cmd->tokens[f_cmd->itoken]);
		*is_command = 1;
		f_cmd->itoken++;
	}
	*start = end;
	return (1);
}
