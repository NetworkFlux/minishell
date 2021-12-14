/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:01:25 by npinheir          #+#    #+#             */
/*   Updated: 2021/12/13 08:16:35 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "minishell_struct.h"
# include "../libft/include/libft.h"

# define MAXCOM 1000
# define MAXLIST 100

int		ft_proces_str(char *str, char **parsed);
void	ft_exec_com(char **parsed);

// Commands
void	ft_echo(char *str);
void	ft_pwd(void);
void	ft_cd(char *str);
void	ft_env(char **env);

// Minishell tils
int		ft_error(int argc);
void	ft_init_shell(void);
char	*ft_clean_arg(char *parsed);;


#endif