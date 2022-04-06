/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_hd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:21:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/04/07 00:45:47 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_write_heredoc(char *input, int fd, t_scmd *s_cmd, size_t i)
{
	if (i != s_cmd->redir->inin - 1)
		return ;
	ft_putendl_fd(input, fd);
	if (input)
		free(input);
}

static void	write_heredoc(t_scmd *scmd, char *file_name)
{
	int		fd;
	char	*input;
	size_t	i;

	i = 0;
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (!fd)
		clear_exit(1);
	while (i < scmd->redir->inin)
	{
		input = readline("> ");
		if (!input)
			exit(130);
		while (ft_strcompare(input, scmd->redir->inin_args[i]) == 0)
		{
			check_write_heredoc(input, fd, scmd, i);
			input = readline("> ");
			if (!input)
				exit(130);
		}
		i++;
	}
	close(fd);
}

static char	*heredoc_secret(char *name)
{
	char	*secret_name;

	secret_name = ft_strcat(".", name);
	secret_name = ft_strcat(secret_name, ".ms");
	return (secret_name);
}

static char	*create_heredoc(t_scmd *s_cmd)
{
	pid_t	pid;
	int		fd;
	char	*file_name;

	fd = 0;
	file_name = NULL;
	g_fcmd->active_heredoc = 1;
	file_name = heredoc_secret(s_cmd->redir->inin_args \
			[s_cmd->redir->inin - 1]);
	pid = fork();
	if (!pid)
	{
		write_heredoc(s_cmd, file_name);
		exit(0);
	}
	else
	{
		wait(NULL);
		g_fcmd->active_heredoc = 0;
	}
	return (file_name);
}

void	apply_hd2(void)
{
	size_t	i;

	i = 0;
	while (i < g_fcmd->nb_scmd)
	{
		if (g_fcmd->s_cmd[i]->redir->inin)
			g_fcmd->s_cmd[i]->redir->here_name = \
				create_heredoc(g_fcmd->s_cmd[i]);
		i++;
	}
}
