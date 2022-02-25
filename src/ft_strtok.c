/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:08:18 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/25 18:59:13 by fcaquard         ###   ########.fr       */
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
static int	ft_strtok(s_cmd_t *s_cmd, size_t start, int is_command)
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
			// else if (is_delimiter(s_cmd->s_cmd[start]))
			// {
			// 	if (!parse_delimiter(s_cmd, &start, &is_command, &i))
			// 		return (0);
			// }
			else
			{
				if (!parse_param(s_cmd, &start, &is_command, &i))
					return (0);
			}
		}
	}
	return (1);
}

int	parse_alt(f_cmd_t *f_cmd)
{
	size_t	i;
	size_t	k;
	s_cmd_t	*current;

	i = 0;
	while (i < f_cmd->nb_scmd && f_cmd->s_cmd[i])
	{
		k = 0;
		current = f_cmd->s_cmd[i];
		if (!count_input(current, 0))
		{
			printf("Error while counting tokens (pre-parsing)\n");
			return (clear_all(f_cmd));
		}
		else
		{
			printf("ntokens: %ld\n", current->ntokens);
			f_cmd->s_cmd[i]->tokens = malloc(sizeof(char *) * current->ntokens);
			if (!current->tokens)
				return (clear_all(f_cmd));
			while (k < current->ntokens)
			{
				f_cmd->s_cmd[i]->tokens[k] = malloc(sizeof(t_token));
				if (!f_cmd->s_cmd[i]->tokens[k])
					return (clear_all(f_cmd));
				f_cmd->s_cmd[i]->tokens[k]->type = undefined;
				k++;
			}
			if (!ft_strtok(f_cmd->s_cmd[i], 0, 1))
			{
				printf("Error while parsing\n");
				return (clear_all(f_cmd));
			}
			else
			{
				// debug
				size_t o = 0;
				printf("# exec: %s\n", current->exec);
				while (o < current->ntokens && current->tokens[o])
				{
					// | the pipes are just there to see if there's no spaces around
					printf("# tk[%ld]: |%s| type:%d\n", o, current->tokens[o]->token, current->tokens[o]->type);
					o++;
				}
				print_redir(f_cmd->s_cmd[i], i + 1);
			}
		}
		i++;
	}
	return (1);
}
