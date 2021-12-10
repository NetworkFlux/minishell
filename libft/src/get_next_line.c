/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:14:28 by npinheir          #+#    #+#             */
/*   Updated: 2021/10/25 12:11:22 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin2(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	if (!s1 && !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (0);
	ft_memmove(res, s1, len1);
	ft_memmove(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	free((char *)s1);
	return (res);
}

static int	has_ret(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_clean(char *str)
{
	int		i;
	char	*res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	*ft_clean_save(char *str)
{
	char	*res;
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	res = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
	if (!res)
		return (0);
	i++;
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	char		*buff;
	int			readbytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !buff)
		return (-1);
	readbytes = 1;
	while (!has_ret(save) && readbytes != 0)
	{
		readbytes = read(fd, buff, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(buff);
			return (-1);
		}
		buff[readbytes] = '\0';
		save = ft_strjoin2(save, buff);
	}
	free(buff);
	*line = ft_clean(save);
	save = ft_clean_save(save);
	if (readbytes == 0)
		return (0);
	return (1);
}
