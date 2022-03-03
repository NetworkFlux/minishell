/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:01:59 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/03 17:10:16 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extracts token from single command's string
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

// looks for the tokens start and end then executes tokenize
static int	ft_strtok(t_scmd *s_cmd)
{	
	size_t	itoken;
	size_t	start;

	itoken = 0;
	start = 0;
	while (start < ft_strlen(s_cmd->instructions))
	{
		while (s_cmd->instructions[start]
			&& ft_isspace(s_cmd->instructions[start]))
			start++;
		if (s_cmd->instructions[start])
		{
			if (!parse_param(s_cmd, &start, &itoken))
				return (0);
		}
	}
	return (1);
}

// allocates memory for the token array
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
		k++;
	}
	return (1);
}

/** 
	Takes every single commands and parses them on 
	every tokens respecting the double quoted blocks,
	single quoted and the ones between parenthesis.
*/
int	parse_cmd(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		if (g_fcmd->s_cmd[i]->instructions)
		{
			if (!count_input(g_fcmd->s_cmd[i], 0))
				return (clear_all());
			else
			{
				if (g_fcmd->s_cmd[i]->ntokens > 0)
				{
					if (!token_memory_alloc(g_fcmd->s_cmd[i]))
						return (0);
					if (!ft_strtok(g_fcmd->s_cmd[i]))
						return (clear_all());
				}
				is_builtin(g_fcmd->s_cmd[i]);
			}
		}
		i++;
	}
	return (1);
}
