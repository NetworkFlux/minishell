/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:01:59 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/05 19:23:45 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// looks for the tokens start and end then executes tokenize
static int	ft_strtok(t_scmd *s_cmd, char *str, int is_exec)
{	
	int	itoken;
	size_t	start;
	char	*tmp;

	itoken = 0;
	start = 0;
	while (str && str[start])
	{
		while (str[start]
			&& ft_isspace(str[start]))
			start++;
		if (str[start])
		{
			tmp = parse_param(str, &start);
			if (!tmp)
				return (0);
			if (is_exec)
			{
				s_cmd->exec = tmp;
				is_exec = 0;
			}
			else
				s_cmd->tokens[itoken++]->token = tmp;
		}
		if (str[start] != '\0')
			start++;
	}
	return (1);
}

// allocates memory for the token array
static int	token_memory_alloc(t_scmd *current)
{
	size_t	k;

	k = 0;
	if (current->ntokens > 0)
	{
		current->tokens = malloc(sizeof(char *) * current->ntokens);
		if (!current->tokens)
			error_malloc();
		while (k < current->ntokens)
		{
			current->tokens[k] = malloc(sizeof(t_token));
			if (!current->tokens[k])
				error_malloc();
			k++;
		}
	}
	return (1);
}

// before parsing, in order to malloc our variables
// count how many tokens we will have (exec not included)
static int	count_input(char *str, size_t start, size_t	*ntokens, int is_exec)
{
	while (str && str[start])
	{
		while (str[start]
			&& ft_isspace(str[start]))
			start++;
		if (str[start])
		{
			start = find_param_end(str, start);
			if (start == 0)
				return (0);
			if (!is_exec)
				(*ntokens)++;
			else
				is_exec = 0;
		}
		if (str[start])
			start++;
	}
	return (1);
}

/** 
	Takes every single commands and parses them on 
	every tokens respecting the double quoted blocks,
	single quoted and the ones between parenthesis.
*/
/*
int	parse_cmd(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		if (g_fcmd->s_cmd[i]->instructions)
		{
			if (!count_input(g_fcmd->s_cmd[i], 0))
			{
				printf("No tokens\n");
				return (clear_all());
			}
			else
			{
				printf("%ld Tokens\n", g_fcmd->s_cmd[i]->ntokens);
				if (g_fcmd->s_cmd[i]->ntokens > 0)
				{
					if (!token_memory_alloc(g_fcmd->s_cmd[i]))
						return (0);
					if (!ft_strtok(g_fcmd->s_cmd[i]))
						return (clear_all());
				}
				print_tokens(g_fcmd->s_cmd[i]);
				is_builtin(g_fcmd->s_cmd[i]);
			}
		}
		i++;
	}
	return (1);
}
*/

int	parse_cmd(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		if (g_fcmd->s_cmd[i]->s_cmd)
		{
			if (!count_input(g_fcmd->s_cmd[i]->s_cmd, 0, &g_fcmd->s_cmd[i]->ntokens, 1))
			{
				printf("No tokens\n");
				return (clear_all());
			}
			else
			{
				printf("%ld Tokens\n", g_fcmd->s_cmd[i]->ntokens);
				if (!token_memory_alloc(g_fcmd->s_cmd[i]))
					return (0);
				if (!ft_strtok(g_fcmd->s_cmd[i], g_fcmd->s_cmd[i]->s_cmd, 1))
					return (clear_all());
				printf("Exec: %s\n", g_fcmd->s_cmd[i]->exec);
				print_tokens(g_fcmd->s_cmd[i]);
				is_builtin(g_fcmd->s_cmd[i]);
			}
		}
		i++;
	}
	return (1);
}