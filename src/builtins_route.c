/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/28 18:01:15 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if the exec is a builtin calls the appropriate function */
static void	route_builtins(t_scmd *scmd, size_t i)
{
	if (i == 0)
		printf("<route_builtins> builtin: echo\n");
	else if (i == 1)
	{
		printf("<route_builtins> builtin: cd\n");
		buildins_cd(scmd);
	}
	else if (i == 2)
	{
		printf("<route_builtins> builtin: pwd\n");
		buildins_pwd(scmd);
	}
	else if (i == 3)
		printf("<route_builtins> builtin: export\n");
	else if (i == 4)
	{
		printf("<route_builtins> builtin: unset\n");
		builtin_unset(scmd);
	}
	else if (i == 5)
		printf("<route_builtins> builtin: env\n");
	else
		printf("<route_builtins> builtin: exit\n");
}

/* checks if the single command exec is a builtin function */
int	is_builtin(t_scmd *s_cmd)
{
	size_t		i;
	const char	*builtins[7] = {"echo", "cd",
		"pwd", "export", "unset", "env", "exit"};

	i = 0;
	while (i < 7 && builtins[i])
	{
		if (ft_strncmp(builtins[i], s_cmd->exec, ft_strlen(s_cmd->exec)) == 0)
		{
			route_builtins(s_cmd, i);
			return (1);
		}
		i++;
	}
	return (0);
}
