/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/15 18:17:03 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if the exec is a builtin and files pernissions are ok, calls the appropriate function */
static void	route_builtins(t_scmd *scmd, size_t i)
{
	if (i == 0)
		buildins_echo(scmd, apply_outredir(scmd));
	else if (i == 1)
		buildins_cd(scmd);
	else if (i == 2)
		buildins_pwd(scmd, apply_outredir(scmd));
	else if (i == 3)
		builtins_export(scmd);
	else if (i == 4)
		builtin_unset(scmd);
	else if (i == 5)
		builtins_env(scmd, apply_outredir(scmd));
	else if (i == 6)
		builtins_exit();
	else if (i == 7)
		buildins_echo(scmd, apply_outredir(scmd));
	else if (i == 8)
		buildins_cat(scmd, apply_outredir(scmd), apply_inredir(scmd));
}

/* checks if the single command exec is a builtin function */
static int	is_builtin(t_scmd *s_cmd)
{
	size_t		i;
	const char	*builtins[8] = {"cd",
		"pwd", "export", "unset", "env", "exit", "echo", "cat"};

	i = 0;
	while (i < 8 && builtins[i])
	{
		if (ft_strcompare(builtins[i], s_cmd->tokens[0]))
		{
			return (i + 1);
		}
		i++;
	}
	return (0);
}

void	route_exec(void)
{
	size_t	i;
	size_t	res;

	i = 0;
	while (i < g_fcmd->nb_scmd && g_fcmd->s_cmd[i])
	{
		res = is_builtin(g_fcmd->s_cmd[i]);
		if (res > 0)
			route_builtins(g_fcmd->s_cmd[i], res);
		else
		{
			printf("not a builtin. --> exec\n");
			exec(g_fcmd->s_cmd[i], g_fcmd->envp);
		}
		i++;
	}
}
