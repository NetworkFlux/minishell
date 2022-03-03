/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:36:18 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/03 17:02:59 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_quotes(char *str, char *master, size_t i, size_t j)
{
	size_t	jump;

	while (master && master[i])
	{
		if (!is_block_start(master[i]))
		{
			str[j] = master[i];
			i++;
			j++;
		}
		else
		{
			jump = find_block_end(master, i);
			i = i + 1;
			while (i != jump && master[i])
			{
				str[j] = master[i];
				i++;
				j++;
			}
			i = i + 1;
		}
	}
	return (str);
}

static int	length_without_quotes(char *str)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	while (str && str[i])
	{
		if (is_block_start(str[i]))
		{
			i = find_block_end(str, i);
			if (i == 0)
				return (-1);
			len -= 2;
		}
		i++;
	}
	return ((int)len);
}

int	remove_quotes(void)
{
	size_t	i;
	char	*str;
	int		len;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		if (g_fcmd->s_cmd[i]->s_cmd)
		{
			len = length_without_quotes(g_fcmd->s_cmd[i]->s_cmd);
			if (len > -1)
			{
				str = malloc(sizeof(char) * len + 1);
				if (!str)
					return (0);
				str = skip_quotes(str, g_fcmd->s_cmd[i]->s_cmd, 0, 0);
				str[len] = '\0';
				g_fcmd->s_cmd[i]->instructions = str;
				printf("<remove_quotes> |%s|\n", g_fcmd->s_cmd[i]->instructions);
			}
		}
		i++;
	}
	return (1);
}
