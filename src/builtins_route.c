/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/17 20:49:14 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if the exec is a builtin and files pernissions are ok, calls the appropriate function */
static void	route_builtins(t_scmd *scmd, size_t i)
{
	if (i == 0)
		buildins_echo(scmd);
	else if (i == 1)
		buildins_cd(scmd);
	else if (i == 2)
		buildins_pwd(scmd);
	else if (i == 3)
		builtins_export(scmd);
	else if (i == 4)
		builtin_unset(scmd);
	else if (i == 5)
		builtins_env(scmd);
	else if (i == 6)
		builtins_exit();
	exit(0);
}

/* checks if the single command exec is a builtin function */
void	is_builtin(t_scmd *s_cmd, char **args)
{
	size_t		i;
	const char	*builtins[7] = {"echo", "cd",
		"pwd", "export", "unset", "env", "exit"};

	if (s_cmd->redir->in || s_cmd->redir->inin)
		args = apply_inredir(s_cmd);
	i = 0;
	while (i < 7 && builtins[i])
	{
		if (ft_strcompare(builtins[i], s_cmd->tokens[0]))
		{
			route_builtins(s_cmd, i);
			return ;
		}
		i++;
	}
	//printf("Child Process : %s is being executed\n", s_cmd->tokens[0]);
	execvp(s_cmd->tokens[0], args);
}

// void	route_exec(char **envp)
// {
// 	size_t	i;
// 	size_t	res;

// 	i = 0;
// 	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
// 	{
// 		res = is_builtin(g_fcmd->s_cmd[i]);
// 		if (res > 0)
// 			route_builtins(g_fcmd->s_cmd[i], res);
// 		else
// 		{
// 			printf("not a builtin. --> exec\n");
// 			exec(g_fcmd->s_cmd[i], envp);
// 		}
// 		i++;
// 	}
// }
