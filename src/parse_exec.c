/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:25:05 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/03 15:48:33 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_exec(t_scmd *scmd, size_t end)
{
	char	*instructions;
	size_t	i;

	i = 0;
	instructions = malloc(sizeof(char) * (ft_strlen(scmd->instructions) - end) + 1);
	if (!instructions)
		return ; // should clear and exit program (malloc error)
	while (scmd->instructions[end])
	{
		instructions[i] = scmd->instructions[end];
		i++;
		end++;
	}
	instructions[i] = '\0';
	free (scmd->instructions);
	scmd->instructions = instructions;
}

static void	set_exec(t_scmd *scmd, size_t start, size_t end)
{
	char	*exec;
	size_t	i;

	i = 0;
	exec = malloc(sizeof(char) * (end - start) + 1);
	if (!exec)
		return ; // should clear and exit program (malloc error)
	while (scmd->instructions[start] && start < end)
	{
		exec[i] = scmd->instructions[start];
		i++;
		start++;
	}
	exec[i] = '\0';
	scmd->exec = exec;
}

void	get_exec(void)
{
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	start = 0;
	end = 0;
	while (g_fcmd->s_cmd && g_fcmd->s_cmd[i] && i < g_fcmd->nb_scmd)
	{
		while (g_fcmd->s_cmd[i]->instructions && ft_isspace(g_fcmd->s_cmd[i]->instructions[start]))
			(start)++;
		end = start;
		while (g_fcmd->s_cmd[i]->instructions
			&& g_fcmd->s_cmd[i]->instructions[end]
			&& !ft_isspace(g_fcmd->s_cmd[i]->instructions[end]))
			(end)++;
		set_exec(g_fcmd->s_cmd[i], start, end);
		remove_exec(g_fcmd->s_cmd[i], end);
		printf("<get_exec> exec: |%s|\n",g_fcmd->s_cmd[i]->exec);
		printf("<get_exec> inst: |%s|\n",g_fcmd->s_cmd[i]->instructions);
		i++;
	}
}

