/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:06:40 by npinheir          #+#    #+#             */
/*   Updated: 2021/12/13 07:29:36 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_clean_arg(char *parsed)
{
	char	*res;
	int		i;
	int		j;

	res = parsed;
	i = 0;
	j = 0;
	while (parsed[i])
	{
		if (parsed[0] == ' ')
			i++;
		res[j] = parsed[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

void	ft_init_shell(void)
{
	printf("\n\n\n\n******************"
		"************************");
	printf("\n\n\n\t****MY SHELL****");
	printf("\n\n\t-USE AT YOUR OWN RISK-");
	printf("\n\n\n\n*******************"
		"***********************");
	printf("\n\n\n");
}

int	ft_error(int argc)
{
	if (argc != 1)
	{
		perror("Wrong usage (./minishell)");
		return (1);
	}
	return (0);
}
