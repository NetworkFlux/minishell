/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:50 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/05 19:45:46 by npinheir         ###   ########.fr       */
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
	if (!scmd->redir->last_out)
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
	char	*tmp;
	char	*tmp2;

	tmp = ft_strcat(scmd->redir->inin_args[scmd->redir->inin - 1], ".ms");
	if (!tmp)
		clear_all();
	tmp2 = ft_strcat(".", tmp);
	if (!tmp2)
		clear_all();
	hered = get_heredoc(scmd);
	fd = open(tmp2, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (!fd)
		clear_all();
	i = 1;
	while (hered[i])
		ft_putendl_fd(hered[i++], fd);
	close(fd);
	free(tmp);
	clear_array(hered, ft_arrlen(hered));
	hered = ft_realloc(scmd->tokens, tmp2);
	free(tmp2);
	return (hered);
}

static char	**heredoc_loop(char *input, char **res, t_scmd *scmd, size_t i)
{
	char	**tmp;

	if (i == scmd->redir->inin - 1)
	{
		tmp = ft_realloc(res, input);
		clear_array(res, ft_arrlen(res));
		if (input)
			free(input);
		res = tmp;
	}
	return (res);
}

char	**get_heredoc(t_scmd *scmd)
{
	char	**res;
	char	*input;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char *) * 2);
	res[0] = ft_strdup(scmd->tokens[0]);
	res[1] = NULL;
	while (i < scmd->redir->inin)
	{
		g_fcmd->active_heredoc = 1;
		input = readline("> ");
		while (ft_strcompare(input, scmd->redir->inin_args[i]) == 0)
		{
			res = heredoc_loop(input, res, scmd, i);
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
	return (tab);
}
