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
	printf("return 0\n");
	return (0);
}

// returns 0 if not a delimiter
// returns end if is a delimiter
static int	find_delimiter_end(char *input, size_t start)
{
	if ((unsigned char) input[start] == '|')
	{
		if (input[start + 1] && input[start + 1] == '|')
		{
			return (start + 2);
		}
		return (start + 1);
	}
	else if ((unsigned char) input[start] == '>')
	{
		if (input[start + 1] && input[start + 1] == '>')
		{
			return (start + 2);
		}
		return (start + 1);
	}
	else if ((unsigned char) input[start] == '<')
	{
		if (input[start + 1] && input[start + 1] == '<')
		{
			return (start + 2);
		}
		return (start + 1);
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

// returns 1 on incomplete input
static int	ft_strtok(char *input, f_cmd_t *f_cmd)
{
	(void)f_cmd;

	char	*token;
	int		is_command;
	size_t	start;
	size_t	end;

	start = 0;
	is_command = 1;
	while (start < ft_strlen(input))
	{
		// printf("START: %ld / [%c] \n", start, input[start]);
		if (is_input_incomplete(input))
		{
			printf("error input\n");
			return (1);
		}
		while (input && ft_isspace(input[start]))
			start++;

		// block "" '' ()
		 // (if first or after a delimiter == command)
		if (is_block_start(input[start])) 
		{
			// printf("is_block: %c\n", input[start]);
			end = find_block_end(input, input[start], start);
			if (end == 0)
			{
				printf("error blockend\n");
			}
			else
			{
				// tokenize block
				token = tokenize(input, start + 1, end);
				if (!token)
					return (1);
				if (is_command)
					printf("is_command ");
				printf("block: ");
				is_command = 0;
				end++;
			}
		}
		else if(ft_isdelimiter(input[start]))
		{
			end = find_delimiter_end(input, start);

			if (end == 0)
			{
				printf("error delimiter\n");
			}
			else
			{
				token = tokenize(input, start, end);
				if (!token)
					return (1);
				printf("delimiter: ");
				is_command = 1;
				end++;
			}
		}
		else // word (if first or after a delimiter == command)
		{
			end = find_token_end(input, start);
			if (end == 0)
			{
				printf("find token bad output\n");
			}
			else
			{
				token = tokenize(input, start, end);
				if (!token)
					return (1);
				// printf("token start: %c / end: %c\n", input[start], input[end]);
				if (is_command)
					printf("is_command ");
				printf("param: ");
				is_command = 0;
				end++;
			}
		}
		printf("|%s|\n", token);
		start = end;
	}
	return (0);
}

int parse_strtok(f_cmd_t *f_cmd)
{
	ft_strtok(f_cmd->f_cmd, f_cmd);
	return (0);
}