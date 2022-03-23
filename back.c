/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 10:04:57 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/23 22:00:48 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

static	int	ft_chknl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	if (i == (int)ft_strlen(s))
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	int	rd;
	char	*s;
	char	*bf;
	char	*tmp;
	static char	*sub;

	s = 0;
	rd = 1;
	bf = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (sub != 0 && (int)ft_strlen(sub) > 0)
	{
		s = ft_strdup(sub);
		free(sub);
		sub = 0;
	}
	while (rd > 0)
	{
		bf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!bf)
			return (0);
		rd = read(fd, bf, BUFFER_SIZE);
		if (rd > 0)
		{
			bf[rd] = 0;
			tmp = ft_strjoin(s, bf);
			free(s);
			s = tmp;
			if (ft_chknl(s) <= (int)ft_strlen(s))
			{
				tmp = ft_substr(s, 0, ft_chknl(s));
				if (ft_chknl(s) != (int)ft_strlen(s))
					sub = ft_substr(s, ft_chknl(s), (int)ft_strlen(s) - ft_chknl(s));
				free(bf);
				free(s);
				return (tmp);
			}
		}
		free(bf);
	}
	if (s != 0 && (int)ft_strlen(s))
	{
		if (ft_chknl(s) < (int)ft_strlen(s))
		{
			tmp = ft_substr(s, 0, ft_chknl(s));
			sub = ft_substr(s, ft_chknl(s), (int)ft_strlen(s) - ft_chknl(s));
			free(s);
			s = tmp;
		}
		return (s);
	}
	return (0);
}
