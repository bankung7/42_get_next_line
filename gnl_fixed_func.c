/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 10:04:57 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/24 12:53:07 by vnilprap         ###   ########.fr       */
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

static char	*ft_getsub(char *s)
{
	char		*tmp;
	static char 	*sub;

	tmp = 0;
	if (s == 0 && sub != 0 && (int)ft_strlen(sub) > 0)
	{
		tmp = ft_strdup(sub);
		free(sub);
		sub = 0;
		return (tmp);
	}
	if (s != 0)
	{
		tmp = ft_strjoin(sub, s);
		free(s);
		free(sub);
		sub = tmp;
		return (0);
	}
	return (0);
}

static char	*ft_getword(char *s, char *bf)
{
	char	*tmp;

	tmp = 0;
	if (ft_chknl(s) <= (int)ft_strlen(s))
	{
		tmp = ft_substr(s, 0, ft_chknl(s));
		if (bf)
			free(bf);
		if (ft_chknl(s) == (int)ft_strlen(s))
		{
			free(s);
			return (tmp);
		}
		ft_getsub(ft_substr(s, ft_chknl(s), (int)ft_strlen(s) - ft_chknl(s)));
		free(s);
		return (tmp);
	}
	return (s);
}

char	*get_next_line(int fd)
{
	int	rd;
	char	*s;
	char	*bf;
	char	*tmp;

	rd = 1;
	bf = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	s = ft_getsub(0);
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

			s = ft_getword(tmp, bf);
			if (ft_chknl(s) <= (int)ft_strlen(s))
				return (s);
			/*
			s = tmp;
			if (ft_chknl(s) <= (int)ft_strlen(s))
			{
				tmp = ft_substr(s, 0, ft_chknl(s));
				free(bf);
				if (ft_chknl(s) == (int)ft_strlen(s))
				{
					free(s);
					return (tmp);
				}
				ft_getsub(ft_substr(s, ft_chknl(s), (int)ft_strlen(s) - ft_chknl(s)));
				free(s);
				return (tmp);
			}
			*/
		}
		free(bf);
	}
	
	
	if (s != 0 && (int)ft_strlen(s))
	{
		return (ft_getword(s, 0));
	/*
		if (ft_chknl(s) < (int)ft_strlen(s))
		{
			tmp = ft_substr(s, 0, ft_chknl(s));
			ft_getsub(ft_substr(s, ft_chknl(s), (int)ft_strlen(s) - ft_chknl(s)));
			free(s);
			s = tmp;
		}
		return (s);
	*/
	}
	return (0);
}
