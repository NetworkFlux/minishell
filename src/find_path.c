/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:22:48 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/21 19:01:59 by fcaquard         ###   ########.fr       */
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

static char	*slash_path(t_scmd *scmd)
{
	size_t	len;
	size_t	i;
	char	*token;
	char	*target;

	i = 0;
	len = ft_strlen(scmd->tokens[0]);
	target = scmd->tokens[0];
	while (len > 0 && scmd->tokens[0][len - 1] && scmd->tokens[0][len - 1] != '/' )
	{
		i++;
		len--;
	}
	token = fillstr(len, len + i, scmd->tokens[0]);
	if (!token)
		return (NULL);
	scmd->tokens[0] = token;
	return (target);
}

// split PATH onto :
// loop & concat with the current exec to create a path to the exec file
// check if file exist
char	*find_path(t_scmd *scmd)
{
	char	**paths;
	char	*target;
	char	*tmp;
	size_t	i;

	target = NULL;
	if (!scmd->tokens || !scmd->tokens[0])
		return (NULL);
	if (access(scmd->tokens[0], F_OK) == 0)
		return (slash_path(scmd));
	i = 0;
	g_fcmd->envp = find_env(g_fcmd->envp, "PATH");
	paths = ft_split(g_fcmd->envp->value, ':');
	if (!paths)
		return (NULL);
	while (paths && paths[i])
	{
		tmp = concat(paths[i], scmd->tokens[0], '/');
		if (access(tmp, F_OK) == 0)
		{
			target = tmp;
			break ;
		}
		free (tmp);
		i++;
	}
	clear_array(paths, ft_arrlen(paths));
	return (target);
}

