/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 07:30:54 by npinheir          #+#    #+#             */
/*   Updated: 2021/12/13 08:16:29 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *str)
{
	if (ft_strncmp(str, "-n ", 3) == 0)
		printf("%s%%\n", str + 3);
	else
		printf("%s\n", str);
}

void	ft_pwd(void)
{
	char	*buff;

	buff = NULL;
	printf("%s\n", getcwd(buff, 1024));
}

void	ft_cd(char *str)
{
	char	*buff;
	char	*path;

	if (ft_strncmp(str, "..", 2) == 0)
	{
		chdir("..");
		return ;
	}
	buff = NULL;
	path = getcwd(buff, 1024);
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, str);
	chdir(path);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}
