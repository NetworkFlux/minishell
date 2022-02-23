/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:51:13 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/23 22:20:17 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO
	same error as in shell for `>>>>` and `<<<<<`
	find a way to link a token and its type (delimiter, option, ...)
	find a way to link a token to its command (multiple tokens between delimiter)
	find a way to link a command to the full input
	test with parenthesis 
*/

static int	is_delimiter(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

// check block start ' " (
static int	is_block_start(char c)
{
	if (
		(unsigned char) c == '\''
		|| (unsigned char) c == '"'
		|| (unsigned char) c == '(')
		return (1);
	return (0);
}

// returns 0 when no blockend is not found / end position on success
static size_t	find_block_end(char *input, size_t position)
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

// returns 0 when no end is not found / end position on success
static size_t	find_token_end(char *input, size_t position)
{
	while (input && input[position])
	{
		if (ft_isspace(input[position]))
			return (position);
		position++;
	}
	if (input[position] == '\0')
		return (position);
	return (0);
}

// returns 0 when end delimiter is not found / end position on success
static size_t	find_delimiter_end(char *input, size_t start)
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
		if (len <= 2)
			return (start);
		printf("bash: syntax error near unexpected token `|'\n");
	}
	else if ((unsigned char) input[start] == '>')
	{
		while (input[start] && input[start] == '>')
		{
			start++;
			len++;
		}
		if (len <= 2)
			return (start);
		printf("bash: syntax error near unexpected token `>'\n");
	}
	else if ((unsigned char) input[start] == '<')
	{
		while (input[start] && input[start] == '<')
		{
			start++;
			len++;
		}
		if (len <= 3)
			return (start);
		printf("bash: syntax error near unexpected token `<'\n");
	}
	return (0);
}

// checks if the ' " ( are closed
int	is_input_incomplete(char *input)
{
	size_t	i;
	size_t	res;

	i = 0;
	while (input && input[i])
	{
		if (is_block_start(input[i]))
		{	
			res = find_block_end(input, i);
			if (res == 0)
				return (1);
			i = res;
		}
		i++;
	}
	return (0);
}

// extracts token from string
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

static int	parse_param(f_cmd_t *f_cmd, size_t *start, int *is_command)
{
	size_t	end;

	end = find_token_end(f_cmd->f_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		f_cmd->tokens[f_cmd->token_index] = tokenize(f_cmd->f_cmd, *start, end);
		if (!f_cmd->tokens[f_cmd->token_index])
			return (0);
		if (*is_command)
			printf("is_command ");
		printf("param: %s\n", f_cmd->tokens[f_cmd->token_index]);
		*is_command = 0;
		f_cmd->token_index++;
		end++;
	}
	*start = end;
	return (1);
}

static int	parse_delimiter(f_cmd_t *f_cmd, size_t *start, int *is_command)
{
	size_t	end;

	end = find_delimiter_end(f_cmd->f_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		f_cmd->tokens[f_cmd->token_index] = tokenize(f_cmd->f_cmd, *start, end);
		if (!f_cmd->tokens[f_cmd->token_index])
			return (0);
		printf("delimiter: %s\n", f_cmd->tokens[f_cmd->token_index]);
		*is_command = 1;
		f_cmd->token_index++;
	}
	*start = end;
	return (1);
}

static int	parse_block(f_cmd_t *f_cmd, size_t *start, int *is_command)
{
	size_t	end;

	end = find_block_end(f_cmd->f_cmd, *start);
	if (end == 0)
		return (0);
	else
	{
		f_cmd->tokens[f_cmd->token_index] = tokenize(f_cmd->f_cmd, *start + 1, end);
		if (!f_cmd->tokens[f_cmd->token_index])
			return (0);
		if (*is_command)
			printf("is_command ");
		printf("block: %s\n", f_cmd->tokens[f_cmd->token_index]);
		*is_command = 0;
		f_cmd->token_index++;
		end++;
	}
	*start = end;
	return (1);
}

// splits the input into tokens
static int	ft_strtok(f_cmd_t *f_cmd, size_t start)
{
	int	is_command;

	is_command = 1;
	while (start < ft_strlen(f_cmd->f_cmd))
	{
		while (f_cmd->f_cmd && ft_isspace(f_cmd->f_cmd[start]))
			start++;
		if (is_block_start(f_cmd->f_cmd[start]))
		{
			if (!parse_block(f_cmd, &start, &is_command))
				return (0);
		}
		else if (is_delimiter(f_cmd->f_cmd[start]))
		{
			if (!parse_delimiter(f_cmd, &start, &is_command))
			{
				printf("Error delimiter\n");
				return (0);
			}
		}
		else
		{
			if (!parse_param(f_cmd, &start, &is_command))
				return (0);
		}
	}
	return (1);
}

// before parsing, count input's tokens
static size_t	count_tokens(f_cmd_t *f_cmd, size_t start, size_t count)
{
	while (start < ft_strlen(f_cmd->f_cmd))
	{
		while (f_cmd->f_cmd && ft_isspace(f_cmd->f_cmd[start]))
			start++;
		if (is_block_start(f_cmd->f_cmd[start]))
		{
			start = find_block_end(f_cmd->f_cmd, start);
			if (start++ == 0)
				return (0);
		}
		else if (is_delimiter(f_cmd->f_cmd[start]))
		{
			start = find_delimiter_end(f_cmd->f_cmd, start);
			if (start == 0)
				return (0);
		}
		else
		{
			start = find_token_end(f_cmd->f_cmd, start);
			if (start++ == 0)
				return (0);
		}
		count++;
	}
	return (count);
}

int	parse_alt(f_cmd_t *f_cmd)
{
	f_cmd->nb_scmd = count_tokens(f_cmd, 0, 0);
	if (!f_cmd->nb_scmd)
		printf("Error while counting tokens (pre-parsing)\n");
	if (f_cmd->nb_scmd > 0)
	{
		f_cmd->tokens = malloc(sizeof(char *) * f_cmd->nb_scmd);
		if (!f_cmd->tokens)
			return (1);
		if (!ft_strtok(f_cmd, 0))
		{
			printf("Error while parsing\n");
		}
		else
		{
			// DEBUG
			size_t i = 0;
			while (f_cmd->tokens[i] && i < f_cmd->nb_scmd)
			{
				printf("debug: %s\n", f_cmd->tokens[i]);
				i++;
			}
		}
	}
	return (0);
}
