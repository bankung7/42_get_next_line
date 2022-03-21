/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 10:04:57 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/21 19:03:47 by vnilprap         ###   ########.fr       */
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
	while (s[i] && s[i] != '\n')
		i++;
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
	static	char	*sub;

	rd = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	s = 0;
	tmp = 0;
	while (rd > 0)
	{
		bf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!bf)
			return (0);
		if (sub != 0)
		{
			s = strdup(sub);
			free(sub);
			sub = 0;
			printf("left : %s\n", s);
		}
		rd = read(fd, bf, BUFFER_SIZE);
		if (rd > 0)
		{
			bf[rd] = 0;
			if (ft_chknl(bf) < (int)ft_strlen(bf))
			{
				sub = ft_substr(bf, 0, ft_chknl(bf) + 1);
				tmp = ft_strjoin(s, sub);
				free(sub);
				free(s);
				s = tmp;
				if ((int)ft_strlen(bf) - ft_chknl(bf) > 0)
					sub = ft_substr(bf, ft_chknl(bf) + 1, ft_strlen(bf) - ft_chknl(bf));
				free(bf);
				return (s);
			}
			else
			{
				tmp = ft_strjoin(s, bf);
				free(s);
				s = tmp;
			}
		}
		free(bf);
	}
	if (s != 0 && ft_strlen(s) > 0)
		return (s);
	return (0);
}
