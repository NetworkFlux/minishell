/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:22:48 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/31 17:41:14 by fcaquard         ###   ########.fr       */
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
		return (NULL);
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
	while (len > 0 && scmd->tokens[0][len - 1]
		&& scmd->tokens[0][len - 1] != '/' )
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

static char	*loop_paths(t_scmd *scmd, char **paths, char *target)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (paths && paths[i])
	{
		tmp = concat(paths[i], scmd->tokens[0], '/');
		if (!tmp)
		{
			clear_array(paths, ft_arrlen(paths));
			return (NULL);
		}
		if (access(tmp, F_OK) == 0)
		{
			target = tmp;
			break ;
		}
		free (tmp);
		i++;
	}
	return (target);
}

// split PATH on :
// loop & concat to get PATH/exec
// checks if file exist
char	*find_path(t_scmd *scmd)
{
	char	**paths;
	t_env	*env_tmp;
	char	*target;

	target = NULL;
	if (!scmd->tokens || !scmd->tokens[0])
		return (NULL);
	if (access(scmd->tokens[0], F_OK | X_OK) == 0)
		return (slash_path(scmd));
	env_tmp = find_env(g_fcmd->envp, "PATH");
	if (!env_tmp)
		return (NULL);
	paths = ft_split(env_tmp->value, ':');
	if (!paths)
		return (NULL);
	target = loop_paths(scmd, paths, target);
	clear_array(paths, ft_arrlen(paths));
	return (target);
}
