/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/05 15:08:07 by npinheir         ###   ########.fr       */
=======
/*   Updated: 2022/03/05 14:10:20 by fcaquard         ###   ########.fr       */
>>>>>>> 457aecb1078473f5c28cb21c29bb7315e408256c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(void)
{
	g_fcmd->envp = env_first(g_fcmd->envp);
	while (g_fcmd->envp)
	{
		printf("declare -x %s=\"%s\"\n", g_fcmd->envp->name, g_fcmd->envp->value);
		if (!g_fcmd->envp->next)
			break ;
		g_fcmd->envp = g_fcmd->envp->next;
	}
}

static int	valid_input(t_scmd *scmd)
{
	if (scmd->ntokens == 0)
	{
		print_envp();
		return (0);
	}
	if (scmd->ntokens != 1
		|| !scmd->tokens
		|| !scmd->tokens[0]
		|| !scmd->tokens[0]->token)
	{
		printf ("error arguments.\n");
		return (0);
	}
	return (1);
}

static void	export_new(char **array)
{
	if (ft_strlen(array[0]))
		g_fcmd->envp = add_env(g_fcmd->envp, array[0], array[1]);
	else
	{
		if (ft_strlen(array[1]))
			printf("bash: export: `=%s': not a valid identifier\n", array[1]);
	}
	free(array);
}

static void	export_update(t_env *tmp, char **array)
{
	tmp->name = array[0];
	tmp->value = array[1];
	free(array);
}

void	builtins_export(t_scmd *scmd)
{
	char	**array;
	t_env	*tmp;

	if (!valid_input(scmd))
		return ;
	array = split_first_occurence(scmd->tokens[0]->token, '=');
	if (!array)
		error_malloc();
	printf("name: |%s| \nva: |%s|\n", array[0], array[1]);
	tmp = find_env(g_fcmd->envp, array[0]);
	if (!tmp)
		export_new(array);
	else
		export_update(tmp, array);
}
