/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:02:06 by npinheir          #+#    #+#             */
/*   Updated: 2021/12/09 11:36:01 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_com(char **parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		if (ft_strncmp(parsed[i], "echo ", 5) == 0)
			printf("%s\n", parsed[i] + 5);
		i++;
	}
}

int	ft_proces_str(char *str, char **parsed)
{
	int	i;

	i = 0;
	while (i < MAXLIST)
	{
		parsed[i] = strsep(&str, ";");
		if (parsed[i] == NULL)
			break ;
		if (ft_strlen(parsed[i]) == 0)
			i--;
		i++;
	}
	return (1);
}

int	ft_take_input(char *str)
{
	char	*buff;

	buff = readline(">>> ");
	if (ft_strlen(buff))
	{
		add_history(buff);
		ft_strcpy(str, buff);
		return (0);
	}
	else
		return (ft_take_input(str));
}

int	main(int argc, char **argv)
{
	char	input_str[MAXCOM];
	char	*parsed_arg[MAXLIST];
	//char	*parsed_arg_pipe[MAXLIST];
	int		exec_flag;

	(void)argv;
	if (ft_error(argc))
		return (1);
	exec_flag = 0;
	ft_init_shell();
	while (1)
	{
		ft_take_input(input_str);
		exec_flag = ft_proces_str(input_str, parsed_arg);
		if (exec_flag)
			ft_exec_com(parsed_arg);
	}
	return (0);
}
