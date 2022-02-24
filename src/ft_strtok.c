/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:08:18 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/24 14:19:59 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extracts token from string
char	*tokenize(char *input, size_t start, size_t end)
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

// splits the input into tokens
static int	ft_strtok(f_cmd_t *f_cmd, size_t start, int is_command)
{
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
				return (0);
		}
		else
		{
			if (!parse_param(f_cmd, &start, &is_command))
				return (0);
		}
	}
	return (1);
}

// i = debug variable
int	parse_alt(f_cmd_t *f_cmd)
{
	size_t	i;

	i = 0;
	if (!count_input(f_cmd, 0) || f_cmd->ntokens == 0 || f_cmd->ncmd == 0)
	{
		printf("Error while counting tokens (pre-parsing)\n");
	}
	else
	{
		printf("tk: %ld / cmd: %ld\n", f_cmd->ntokens, f_cmd->ncmd);
		f_cmd->tokens = malloc(sizeof(char *) * f_cmd->ntokens);
		if (!f_cmd->tokens)
			return (1);
		if (!ft_strtok(f_cmd, 0, 1))
		{
			printf("Error while parsing\n");
		}
		else
		{
			while (f_cmd->tokens[i] && i < f_cmd->ntokens)
			{
				printf(">>debug: %s\n", f_cmd->tokens[i]);
				i++;
			}
		}
	}
	return (0);
}
