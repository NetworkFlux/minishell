/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:20:16 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/23 11:20:16 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isdelimiter(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

// check block start ' " (
static	int is_block_start(char c)
{
	if (
		(unsigned char) c == '\''
		|| (unsigned char) c == '"'
		|| (unsigned char) c == '(')
		return (1);
	return (0);
}

// returns 0 when no blockend is found
static	size_t	find_block_end(char *input, char target, size_t position)
{
	if (target == '(')
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

static	int	find_token_end(char *input, size_t position)
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

// returns 0 if not a delimiter
// returns end if is a delimiter
static int	find_delimiter_end(char *input, size_t start)
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
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 1);
		return (0);
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
		ft_putendl_fd("bash: syntax error near unexpected token `>'", 1);
		return (0);
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
		ft_putendl_fd("bash: syntax error near unexpected token `<'", 1);
		return (0);
	}
	return (0);
}

int	is_input_incomplete(char *input)
{
	size_t	i;
	size_t	res;

	i = 0;
	while (input && input[i])
	{
		if (is_block_start(input[i]))
		{	
			res = find_block_end(input, input[i], i);
			if (res == 0)
				return (1);
			i = res;
		}
		i++;
	}
	return (0);
}

static char	*tokenize(char *input, size_t start, size_t end)
{
	char *token;
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


static	int	parse_param(char *input, size_t *start, int *is_command, f_cmd_t *f_cmd)
{
	(void)f_cmd;
	size_t	end;
	char	*token;

	end = find_token_end(input, *start);
	if (end == 0)
	{
		printf("find token bad output\n");
		return (1);
	}
	else
	{
		token = tokenize(input, *start, end);
		if (!token)
			return (1);
		if (*is_command)
			printf("is_command ");
		printf("param: %s\n", token);
		*is_command = 0;
		end++;
	}
	*start = end;
	return (0);
}

static	int parse_delimiter(char *input, size_t *start, int *is_command, f_cmd_t *f_cmd)
{
	(void)f_cmd;
	size_t	end;
	char	*token;

	end = find_delimiter_end(input, *start);
	if (end == 0)
		return (1);
	else
	{
		token = tokenize(input, *start, end);
		if (!token)
			return (1);
		printf("delimiter: %s\n", token);
		*is_command = 1;
	}
	*start = end;
	return (0);
}

static	int parse_block(char *input, size_t *start, int *is_command, f_cmd_t *f_cmd)
{
	(void)f_cmd;
	size_t	end;
	char	*token;

	end = find_block_end(input, input[*start], *start);
	if (end == 0)
	{
		printf("error blockend\n");
		return (1);
	}
	else
	{
		// tokenize block
		token = tokenize(input, *start + 1, end);
		if (!token)
			return (1);
		if (*is_command)
			printf("is_command ");
		printf("block: %s\n", token);
		*is_command = 0;
		end++;
	}
	*start = end;
	return (0);
}

// returns 1 on incomplete input
int	ft_strtok(char *input, size_t start, f_cmd_t *f_cmd)
{
	int is_command;

	is_command = 1;
	while (start < ft_strlen(input))
	{
		while (input && ft_isspace(input[start]))
			start++;
		if (is_block_start(input[start])) 
		{
			if (parse_block(input, &start, &is_command, f_cmd))
				return (1);
		}
		else if(ft_isdelimiter(input[start]))
		{
			if (parse_delimiter(input, &start, &is_command, f_cmd))
				return (1);
		}
		else
		{
			if (parse_param(input, &start, &is_command, f_cmd))
				return (1);
		}
	}
	return (0);
}