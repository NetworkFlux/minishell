/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:36:18 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/17 16:26:47 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*skip_quotes(char *master, char *str, size_t i, size_t j)
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

char	*remove_quotes(char *input)
{
	char	*output;
	int		len;

	len = length_without_quotes(input);
	if (len > -1)
	{
		output = malloc(sizeof(char) * len + 1);
		if (!output)
			error_malloc();
		output = skip_quotes(input, output, 0, 0);
		output[len] = '\0';
		// g_fcmd->s_cmd[i]->instructions = output;
		// printf("<remove_quotes> |%s|\n", output);
		return (output);
	}
	return (NULL);
}
