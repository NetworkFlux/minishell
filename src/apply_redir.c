/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:04:50 by npinheir          #+#    #+#             */
/*   Updated: 2022/03/16 15:26:38 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_redir_file_s(t_scmd *scmd)
{
	size_t	i;
	int		temp;

	temp = 1;
	i = 0;
	while (scmd->redir->out_args[i] && i < scmd->redir->out - 1)
	{
		temp = open(scmd->redir->out_args[i++], O_CREAT | O_WRONLY, 0777);
		if (!temp)
			return; // gerer l'erreur
		close(temp);
	}
}

void	create_redir_file_d(t_scmd *scmd)
{
	size_t	i;
	int		temp;

	temp = 1;
	i = 0;
	while (scmd->redir->outout_args[i] && i < scmd->redir->out - 1)
	{
		temp = open(scmd->redir->outout_args[i++], O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (!temp)
			return; // gerer l'erreur
		close(temp);
	}
}

// creates all de desired files and closes them but leaves the last one open
int		apply_outredir(t_scmd *scmd)
{
	int		fd;
	int		temp;

	temp = 1;
	if (!scmd->redir->out && !scmd->redir->outout)
		return (1);
	create_redir_file_s(scmd);
	temp = open(scmd->redir->out_args[scmd->redir->out - 1], O_CREAT | O_WRONLY, 0777);
	if (!temp)
		return (1); // gere l'erreur
	fd = temp;
	create_redir_file_d(scmd);
	temp = open(scmd->redir->outout_args[scmd->redir->outout - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (!temp)
		return (1); // gere l'erreur
	if (scmd->redir->last_out == 2)
	{
		close(fd);
		fd = temp;
	}
	else
		close(temp);
	return (fd);
}

char	**get_fdin_data(t_scmd *scmd, int fd)
{
	char	**res;
	char	*line;
	size_t	fd_len;
	size_t	i;

	line = NULL;
	fd_len = charsslen(fd);
	res = malloc(sizeof(char *) * (fd_len + 1));
	fd = open(scmd->redir->in_args[scmd->redir->in - 1], O_RDONLY);
	if (!res || !fd)
		return NULL;
	i = 0;
	while (get_next_line(fd, &line))
	{
		res[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!res[i])
			return (NULL);
		res[i] = line;
		res[i++][ft_strlen(line)] = '\0';
	}
	res[i] = NULL;
	return (res);
}

char	**apply_heredoc(t_scmd *scmd)
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
		input = readline("> ");
		while (ft_strncmp(input, scmd->redir->inin_args[i], ft_strlen(scmd->redir->inin_args[i])) != 0)
		{
			if (i == scmd->redir->inin - 1)
				res = ft_realloc(res, input);
			input = readline("> ");
		}
		i++;
	}
	return (res);
}

char	**apply_inredir(t_scmd *scmd)
{
	int		fd;
	char	**tab;

	tab = NULL;
	fd = 0;
	if (!scmd->redir->in && !scmd->redir->inin)
	{
		tab = scmd->tokens;
		return (tab);
	}
	if (scmd->redir->last_in == 1)
	{
		fd = open(scmd->redir->in_args[scmd->redir->in - 1], O_RDONLY);
		if (!fd)
			return (NULL);
		tab = get_fdin_data(scmd, fd);
		close(fd);
	}
	else
		tab = apply_heredoc(scmd);
	return (tab);
}