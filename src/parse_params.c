/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:45:23 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/05 19:47:51 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks for quotes
int	is_block_start(char c)
{
	if ((unsigned char) c == '\''
		|| (unsigned char) c == '"')
		return (1);
	return (0);
}

// returns block's end's position
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
	return (position);
}

// looks for a space not between quotes
size_t	find_param_end(char *input, size_t position)
{
	while (input && input[position])
	{
		if (is_block_start(input[position]))
			position = find_block_end(input, position);
		if (ft_isspace(input[position]))
			return (position);
		else
			position++;
	}
	if (input[position] == '\0')
		return (position);
	return (0);
}

// copies the input into a token
// returns a token (char *)
static char	*tokenize(char *input, size_t start, size_t end)
{
	char	*token;
	size_t	i;

	i = 0;
	token = malloc(sizeof(char) * (end - start) + 1);
	if (!token)
		return (NULL);
	token[end - start] = '\0';
	while (input && input[start] && start < end)
		token[i++] = input[start++];
	return (token);
}

// copies str up until it founds a space (not between quotes)
// returns a token (char µ) and updates *start to where it stopped
char	*parse_param(char *str, size_t *start)
{
	size_t	end;
	char	*token;

	token = NULL;
	end = find_param_end(str, *start);
	if (end != 0)
	{
		token = tokenize(str, *start, end);
		if (!token)
			error_malloc();
		token = remove_quotes(token);
	}
	*start = end;
	return (token);
}
