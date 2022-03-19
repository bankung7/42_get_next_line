/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 10:04:57 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/20 06:16:52 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

static	int	ft_getpos(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != c)
		i++;
	if (i == (int)ft_strlen(s1))
		return (-1);
	return (i);
}

char	*get_next_line(int fd)
{
	int	rd;
	char	*s;
	char	*bf;
	static char *sub;

	s = 0;
	rd = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!bf)
		 return (0);
	while (rd > 0)
	{
		rd = read(fd, bf, BUFFER_SIZE);
		bf[rd] = 0;
		printf("read %d bytes\n", rd);
		if (sub != 0)
		{
			free(s);
			s = ft_strjoin(s, sub);
			free(sub);
		}
		if (ft_getpos(bf, '\n') >= 0)
		{
			if (ft_strlen(bf) != 1)
			{
				printf("there\n");
				sub = ft_substr(bf, ft_getpos(bf, '\n') + 1, rd);
				bf = ft_substr(bf, 0, ft_getpos(bf, '\n') + 1);
			}
			s = ft_strjoin(s, bf);
			free(bf);
			return (s);
		}
		s = ft_strjoin(s, bf);
	}
	free(bf);
	if (ft_strlen(s) > 0)
	{
		printf("here\n");
		return (s);
	}
	free(s);
	return (0);
}
