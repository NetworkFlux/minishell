/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:50 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/31 18:49:20 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates all de desired files and closes 
// them but leaves the last one open
int	apply_outredir(t_scmd *scmd)
{
	int		fd;
	int		temp;

	temp = 1;
	if (!scmd->redir->out && !scmd->redir->outout)
		return (1);
	create_redir_file_s(scmd);
	temp = open(scmd->redir->out_args[scmd->redir->out - 1], \
		O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (!temp)
		clear_all();
	fd = temp;
	create_redir_file_d(scmd);
	temp = open(scmd->redir->outout_args[scmd->redir->outout - 1], \
		O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (!temp)
		clear_all();
	if (scmd->redir->last_out == 2)
	{
		close(fd);
		fd = temp;
	}
	else
		close(temp);
	return (fd);
}

char	**apply_heredoc(t_scmd *scmd)
{
	char	**hered;
	int		fd;
	int		i;

	hered = get_heredoc(scmd);
	fd = open("heredoc.ms", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (!fd)
		clear_all();
	i = 1;
	while (hered[i])
		ft_putendl_fd(hered[i++], fd);
	close(fd);
	return (ft_realloc(scmd->tokens, "heredoc.ms"));
}

char	**get_heredoc(t_scmd *scmd)
{
	char	**res;
	char	*input;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char *) * 2);
	res[0] = scmd->tokens[0];
	res[1] = NULL;
	while (i < scmd->redir->inin)
	{
		g_fcmd->active_heredoc = 1;
		input = readline("> ");
		while (ft_strcompare(input, scmd->redir->inin_args[i]) == 0)
		{
			if (i == scmd->redir->inin - 1)
				res = ft_realloc(res, input);
			input = readline("> ");
		}
		i++;
	}
	g_fcmd->active_heredoc = 0;
	return (res);
}

char	**apply_inredir(t_scmd *scmd)
{
	char	**tab;

	tab = NULL;
	if (!scmd->redir->in && !scmd->redir->inin)
	{
		tab = scmd->tokens;
		return (tab);
	}
	if (scmd->redir->last_in == 1)
	{
		tab = scmd->tokens;
		tab = ft_realloc(tab, scmd->redir->in_args[scmd->redir->in - 1]);
	}
	else
		tab = apply_heredoc(scmd);
	return (tab);
}
