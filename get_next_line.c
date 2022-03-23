/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 10:04:57 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/23 19:23:49 by vnilprap         ###   ########.fr       */
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

static char 	*ft_chksub(char *s)
{
	char		*tmp;
	static char	*sub;

	tmp = 0;
	if (s == 0 && sub == 0)
		return (0);
	if (s == 0 && sub != 0 && (int)ft_strlen(sub) > 0)
	{
		s = ft_strdup(sub);
		free(sub);
		sub = 0;
		return (s);
	}
	if (ft_chknl(s) < (int)ft_strlen(s))
	{
		tmp = ft_substr(s, 0, ft_chknl(s));
		sub = ft_substr(s, ft_chknl(s), (int)ft_strlen(s) - ft_chknl(s));	
		free(s);
		return (tmp);
	}
	sub = ft_strdup(s);
	free(s);
	s = 0;
	printf("false here\n");
	return (0);
}

char	*get_next_line(int fd)
{
	int	rd;
	char	*s;
	char	*bf;
	char	*tmp;

	s = 0;
	rd = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	s = ft_chksub(0);
	while (rd > 0)
	{
		bf = 0;
		bf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!bf)
		{
			free(s);
			return (0);
		}
		rd = read(fd, bf, BUFFER_SIZE);
		if (rd > 0)
		{
			bf[rd] = 0;
			tmp = ft_strjoin(s, bf);
			free(s);
			s = tmp;
			printf("%s\n", s);
			tmp = ft_chksub(s);
			if(tmp != 0)
			{
				free(bf);
				return (tmp);
			}
		}
		free(bf);
	}
	printf("here with %s\n", s);
	return (0);
}
