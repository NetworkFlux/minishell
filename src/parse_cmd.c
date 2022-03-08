/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:01:59 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/08 10:50:59 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// looks for the tokens start and end then executes tokenize
static int	ft_strtok(t_scmd *s_cmd, char *str)
{	
	int	itoken;
	size_t	start;
	char	*tmp;

	itoken = 0;
	start = 0;
	while (str && str[start])
	{
		while (str[start] && ft_isspace(str[start]))
			start++;
		if (str[start])
		{
			tmp = parse_param(str, &start);
			if (tmp)
			{
				s_cmd->tokens[itoken++] = tmp;
			}
		}
		if (str[start] != '\0')
			start++;
	}
	return (1);
}

// allocates memory for the token array
static int	token_memory_alloc(t_scmd *current)
{
	// size_t	i;

	// i = 0;
	if (current->ntokens > 0)
	{
		current->tokens = malloc(sizeof(char *) * current->ntokens + 1);
		if (!current->tokens)
			error_malloc();
		current->tokens[current->ntokens] = "\0";
	}
	return (1);
}

// before parsing, in order to malloc our tokens
// count how many tokens we will have (exec not included)
// updates scmd->ntokens directly 
static int	count_input(char *str, size_t start, size_t	*ntokens)
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
			(*ntokens)++;
		}
		if (str[start])
			start++;
	}
	return (1);
}

// counts tokens in order to malloc token's array
// create exec, tokens, then removes their quotes
int	parse_cmd(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		if (g_fcmd->s_cmd[i]->s_cmd)
		{
			if (!count_input(g_fcmd->s_cmd[i]->s_cmd, 0, &g_fcmd->s_cmd[i]->ntokens))
			{
				printf("No tokens\n");
				return (clear_all());
			}
			else
			{
				printf("%ld Tokens\n", g_fcmd->s_cmd[i]->ntokens);
				if (!token_memory_alloc(g_fcmd->s_cmd[i]))
					return (0);
				if (!ft_strtok(g_fcmd->s_cmd[i], g_fcmd->s_cmd[i]->s_cmd))
					return (clear_all());
				printf("Exec: %s\n", g_fcmd->s_cmd[i]->tokens[0]);
				print_tokens(g_fcmd->s_cmd[i]);
			}
		}
		i++;
	}
	return (1);
}