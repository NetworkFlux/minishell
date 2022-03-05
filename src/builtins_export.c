/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/05 15:08:07 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_envp(void)
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

/* NOT WORKING YET */
void	builtins_export(t_scmd *scmd)
{
	char	**array;
	t_env	*tmp;

	if (scmd->ntokens == 0)
	{
		print_envp();
		return ;
	}
	if (scmd->ntokens != 1
		|| !scmd->tokens
		|| !scmd->tokens[0]
		|| !scmd->tokens[0]->token)
	{
		printf ("error arguments.\n");
		return ;
	}
	array = split_first_occurence(scmd->tokens[0]->token, '=');
	if (!array)
		return ; // todo !
	printf("name: |%s| \nva: |%s|\n", array[0], array[1]);
	tmp = find_env(g_fcmd->envp, array[0]);
	if (!tmp)
	{
		printf("NEW ADD\n");
		g_fcmd->envp = add_env(g_fcmd->envp, array[0], array[1]);
		printf("DONE ADD\n");
	}
	else
	{
		printf("UPDATE\n");
		tmp->name = array[0];
		tmp->value = array[1];
		printf("DONE UPDATE\n");
	}
	print_envp();
}
