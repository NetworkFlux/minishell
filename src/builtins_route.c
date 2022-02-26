/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:28:02 by fcaquard          #+#    #+#             */
/*   Updated: 2022/02/26 22:57:03 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	route_builtins(size_t i)
{
	if (i == 0)
		printf("builtin: echo\n");
	else if (i == 1)
		printf("builtin: cd\n");
	else if (i == 2)
		printf("builtin: pwd\n");
	else if (i == 3)
		printf("builtin: export\n");
	else if (i == 4)
		printf("builtin: unset\n");
	else if (i == 5)
		printf("builtin: env\n");
	else
		printf("builtin: exit\n");
}

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
			route_builtins(i);
			return (1);
		}
		i++;
	}
	return (0);
}
