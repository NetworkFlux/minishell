/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:02:06 by npinheir          #+#    #+#             */
/*   Updated: 2021/12/13 08:16:46 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env;

void	ft_exec_com(char **parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		parsed[i] = ft_clean_arg(parsed[i]);
		if (ft_strncmp(parsed[i], "echo ", 5) == 0)
			ft_echo(parsed[i] + 5);
		else if (ft_strncmp(parsed[i], "pwd", 3) == 0)
			ft_pwd();
		else if (ft_strncmp(parsed[i], "cd ", 3) == 0)
			ft_cd(parsed[i] + 3);
		// else if (ft_strncmp(parsed[i], "export ", 7) == 0)
		// 	ft_export();
		// else if (ft_strncmp(parsed[i], "unset ", 6) == 0)
		// 	ft_enset();
		else if (ft_strncmp(parsed[i], "env", 3) == 0)
			ft_env(env);
		else if (ft_strncmp(parsed[i], "exit", 4) == 0)
			exit(EXIT_SUCCESS);
		i++;
	}
}


/*	Fonction qui separe les commandes separes de ;*/
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

int	main(int argc, char **argv, char **envp)
{
	char	input_str[MAXCOM];
	char	*parsed_arg[MAXLIST];
	//char	*parsed_arg_pipe[MAXLIST];
	
	(void)argv;
	env = envp;
	if (ft_error(argc))
		return (1);
	ft_init_shell();
	while (1)
	{
		ft_take_input(input_str);
		ft_proces_str(input_str, parsed_arg);
		ft_exec_com(parsed_arg);
	}
	return (0);
}
