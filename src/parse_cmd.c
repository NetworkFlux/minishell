/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:01:59 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/02 21:12:33 by fcaquard         ###   ########.fr       */
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
		while (s_cmd->instructions[start] && ft_isspace(s_cmd->instructions[start]))
			start++;
		if (s_cmd->instructions[start])
		{
			// if (is_block_start(s_cmd->instructions[start]))
			// {
			// 	if (!parse_block(s_cmd, &start, &itoken))
			// 		return (0);
			// }
			// else
			// {
			// }
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
		current->tokens[k]->type = undefined;
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
	t_scmd	*current;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		printf("<parse_cmd> #1\n");
		if (g_fcmd->s_cmd[i]->instructions)
		{
			printf("<parse_cmd> #2\n");
			current = g_fcmd->s_cmd[i];
			if (!count_input(current, 0))
			{
				return (clear_all());
			}
			else
			{
				printf("<parse_cmd> #3\n");
				if (current->ntokens > 0)
				{
					printf("<parse_cmd> #4\n");
					printf("<parse_cmd> ntokens: %ld\n", current->ntokens);
					if (!token_memory_alloc(current))
						return (0);
					if (!ft_strtok(current))
						return (clear_all());
				}
				is_builtin(current);
				print_cmd(i);
			}
		}
		i++;
	}
	return (1);
}
