/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:02:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/02/25 18:24:11 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// concats previous input with new input
static	char *total_input(char *cmd, char *tmp)
{
	char *total;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	total = malloc(sizeof(char) * (ft_strlen(cmd) + ft_strlen(tmp)) + 1);
	if (!total)
	{
		free(cmd);
		free(tmp);
		return (NULL);
	}
	while (cmd && cmd[i])
		total[j++] = cmd[i++];
	i = 0;
	while (tmp && tmp[i])
		total[j++] = tmp[i++]; 
	total[(ft_strlen(cmd) + ft_strlen(tmp))] = '\0';
	free (cmd);
	free (tmp);
	return (total);
}

char	*take_input(void)
{
	char	*cmd;
	char	*tmp;

	cmd = readline("minishell => ");
	if (!ft_strlen(cmd))
	{
		free(cmd); // even if there's nothing \0 is malloc'd by readline
		cmd = take_input();
	}
	else
	{
		while (cmd && is_input_incomplete(cmd))
		{
			tmp = readline("> ");
			cmd = total_input(cmd, tmp);
		}
		if (!cmd)
			return (NULL);
		add_history(cmd);
	}
	return (cmd);
}

/*
// creating a list of dummy s_cmd
f_cmd_t *test(f_cmd_t *cmd)
{
	s_cmd_t *t;
	s_cmd_t *s;
	s_cmd_t *u;
	t = malloc(sizeof(s_cmd_t) * 1);
	if (!t)
		return (NULL);
	s = malloc(sizeof(s_cmd_t) * 1);
	if (!t)
		return (NULL);
	u = malloc(sizeof(s_cmd_t) * 1);
	if (!t)
		return (NULL);
	t->s_cmd = "echo 'bla'";
	t->ntokens = 0;
	t->tokens = NULL;
	s->s_cmd = "grep  	'space and    time'";
	s->ntokens = 0;
	s->tokens = NULL;
	u->s_cmd = "cat -e 'preparing stuff'";
	u->ntokens = 0;
	u->tokens = NULL;
	cmd->s_cmd = malloc(sizeof(s_cmd_t *) * 3);
	if (!cmd->s_cmd)
		return (NULL);
	cmd->s_cmd[0] = t;
	cmd->s_cmd[1] = s;
	cmd->s_cmd[2] = u;
	cmd->nb_scmd = 3;
	return (cmd);
}
*/

int	main(int argc, char **argv)
{
	(void)argv;
	f_cmd_t	*f_cmd;
	char	*cmd;

	if (argc != 1)
	{
		ft_putendl_fd("Usage : ./minishell", 1);
		return (1);
	}
	clear_on_kill();
	while (1)
	{
		cmd = take_input();
		if (!cmd)
			return (0);
		f_cmd = init_full_cmd(cmd);
		if (!f_cmd)
			return (0);
		else
		{
			parse_redir(f_cmd);
			parse_alt(f_cmd);
			clear_all(f_cmd);
		}
	}
	return (0);
}
