/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:22:48 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/21 17:24:07 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// concats 2 strings with a char c as a separator/link
static char	*concat(char *first, char *append, char c)
{
	char	*new;
	size_t	i;
	size_t	j;
	i = 0;
	j = 0;
	new = malloc (sizeof(char) * ft_strlen(first) + ft_strlen(append) + 2);
	if (!new)
		error_malloc(1);
	while (first && first[i])
	{
		new[j] = first[i];
		i++;
		j++;
	}
	new[j++] = c;
	i = 0;
	while (append && append[i])
	{
		new[j] = append[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

// split PATH onto :
// loop & concat with the current exec to create a path to the exec file
// check if file exist
char	*find_path(t_scmd *scmd)
{
	char	**paths;
	char	*target;
	size_t	i;

	target = NULL;
	if (!scmd->tokens || !scmd->tokens[0])
		return (NULL);
	if (access(scmd->tokens[0], F_OK) == 0)
		return (scmd->tokens[0]);
	i = 0;
	g_fcmd->envp = find_env(g_fcmd->envp, "PATH");
	paths = ft_split(g_fcmd->envp->value, ':');
	if (!paths)
		return (NULL);
	while (paths && paths[i])
	{
		target = concat(paths[i], scmd->tokens[0], '/');
		if (access(target, F_OK) == 0)
			break ;
		free (target);
		i++;
	}
	clear_array(paths, ft_arrlen(paths));
	return (target);
}

