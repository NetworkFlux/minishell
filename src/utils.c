/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 08:07:29 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/25 21:53:36 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir(t_scmd	*s_cmd, size_t j)
{
	size_t	i;

	printf("Current string without redir : %s\n", s_cmd->s_cmd);

	printf("Out redir in simple command %ld : %ld\n", j, s_cmd->redir->out);
	i = 0;
	while (i < s_cmd->redir->out)
	{
		printf("Out target %ld : %s\n", i + 1, s_cmd->redir->out_args[i]);
		i++;
	}
	printf("In redir in simple command %ld : %ld\n", j, s_cmd->redir->in);
	i = 0;
	while (i < s_cmd->redir->in)
	{
		printf("In target %ld : %s\n", i + 1, s_cmd->redir->in_args[i]);
		i++;
	}
	printf("Out out redir in simple command %ld : %ld\n", j, s_cmd->redir->outout);
	i = 0;
	while (i < s_cmd->redir->outout)
	{
		printf("Out out target %ld : %s\n", i + 1, s_cmd->redir->outout_args[i]);
		i++;
	}	
	printf("In in redir in simple command %ld : %ld\n", j, s_cmd->redir->inin);
	i = 0;
	while (i < s_cmd->redir->inin)
	{
		printf("In in target %ld : %s\n", i + 1, s_cmd->redir->inin_args[i]);
		i++;
	}
}

// Retourne le primier mot d'un str
char	*first_word(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	j = i;
	while (str[i] && str[i] != ' ')
		i++;
	res = malloc(sizeof(char) * (i - j + 1));
	if (!res)
		return (NULL);
	res[i - j] = '\0';
	i = j;
	j = 0;
	while (str[i] && str[i] != ' ')
		res[j++] = str[i++];
	return (res);
}

// Return 1 if the caracter at index index is between simple or double quotes
int	is_in_quote(const char *s, int index)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (i < index)
	{
		if (s[i] == 39)
		{
			if (!d_quote)
				s_quote = !s_quote;
		}
		else if (s[i] == '"')
		{
			if (!s_quote)
				d_quote = !d_quote;
		}
		i++;
	}
	return (s_quote || d_quote);
}

// Removes spaces if str starts spaces
char	*remove_spaces(char *str)
{
	size_t	j;
	size_t	k;
	char	*temp;

	j = 0;
	k = 0;
	while (str[j] && str[j] == ' ')
		j++;
	temp = malloc(sizeof(char) * ft_strlen(str) + 1 - j);
	if (!temp)
		return (NULL);
	while (str[j])
	{
		temp[k] = str[j];
		j++;
		k++;
	}
	temp[k] = '\0';
	free(str);
	return (temp);
}