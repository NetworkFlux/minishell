/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:01:59 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/26 22:49:46 by fcaquard         ###   ########.fr       */
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
static int	ft_strtok(t_scmd *s_cmd, size_t start, int is_command)
{	
	size_t	i;

	i = 0;
	while (start < ft_strlen(s_cmd->s_cmd))
	{
		while (s_cmd->s_cmd[start] && ft_isspace(s_cmd->s_cmd[start]))
			start++;
		if (s_cmd->s_cmd[start])
		{
			if (is_block_start(s_cmd->s_cmd[start]))
			{
				if (!parse_block(s_cmd, &start, &is_command, &i))
					return (0);
			}
			else
			{
				if (!parse_param(s_cmd, &start, &is_command, &i))
					return (0);
			}
		}
	}
	return (1);
}

static int	token_memory_alloc(t_scmd *current)
{
	size_t	k;

	k = 0;
	current->tokens = malloc(sizeof(char *) * current->ntokens);
	if (!current->tokens)
		return (clear_all());
	while (k < current->ntokens)
	{
		current->tokens[k] = malloc(sizeof(t_token));
		if (!current->tokens[k])
			return (clear_all());
		current->tokens[k]->type = undefined;
		k++;
	}
	return (1);
}

int	parse_cmd(void)
{
	size_t	i;
	t_scmd	*current;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		current = g_fcmd->s_cmd[i];
		if (!count_input(current, 0))
			return (clear_all());
		else
		{
			printf("ntokens: %ld\n", current->ntokens);
			if (!token_memory_alloc(current))
				return (0);
			if (!ft_strtok(current, 0, 1))
				return (clear_all());
			is_builtin(current);
		}
		i++;
	}
	return (1);
}
