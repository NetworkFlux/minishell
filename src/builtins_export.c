/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:56:38 by fcaquard          #+#    #+#             */
/*   Updated: 2022/03/19 15:42:07 by fcaquard         ###   ########.fr       */
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

// checks if the string provided is only alphanumerical
static int	ft_strisalpha(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// counts until if finds char c
static size_t	count_to_separator(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

// fills dest with the content of src from the value of start to the value of end
static char	*fill_split(size_t start, size_t end, const char *src, char *dest)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = end - start;
	if (start > end)
		size = 0;
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (start < end && src && src[start])
	{
		dest[i] = src[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

//	"str0(separator char)str1" array[2] IS NULL
char	**split_on_first_separator(char *str, char c)
{
	size_t	i;
	char	**array;

	i = count_to_separator(str, c);
	array = malloc(sizeof(char *) * (2 + 1));
	if (!array)
		return (NULL);
	array[2] = NULL;
	array[0] = fill_split(0, i, str, array[0]);
	if (!array[0])
	{
		free(array);
		return (NULL);
	}
	array[1] = fill_split(i + 1, ft_strlen(str), str, array[1]);
	if (!array[1])
	{
		free(array[0]);
		free(array);
		return (NULL);
	}
	return (array);
}

static int	valid_input(t_scmd *scmd)
{
	if (scmd->tokens && scmd->ntokens == 1)
	{
		print_envp();
		exit(0);
	}
	if (!scmd->tokens[1])
	{
		printf ("Error arguments.\n"); // remove
		exit(2);
	}
	return (1);
}

static void	export_new(char **array)
{
	char	*str;

	if (ft_strlen(array[0]))
	{
		str = malloc(sizeof(char) * ft_strlen(array[0]) + \
			ft_strlen(array[1]) + 4);
		if (!str)
			error_malloc(1);
		str = strrebuild(array[0], "=", array[1]);
		g_fcmd->envp = add_env(g_fcmd->envp, array[0], array[1], str);
	}
	clear_array(array, ft_arrlen(array));
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

	valid_input(scmd);
	array = split_on_first_separator(scmd->tokens[1], '=');
	if (!array)
		error_malloc(1);
	if (!ft_strisalpha(array[0]))
	{
		printf("bash: export: `%s': not a valid identifier\n", array[0]);
		exit(1);
	}
	tmp = find_env(g_fcmd->envp, array[0]);
	if (!tmp)
		export_new(array);
	else
		export_update(tmp, array);
	printf("NOLOL\n");
	exit(0);
}
