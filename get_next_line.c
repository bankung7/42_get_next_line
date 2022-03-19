/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 10:04:57 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/19 10:12:57 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int	rd;
	static char	*s;
	char	*bf;

	rd = 1;
	s = 0;
	bf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!bf)
		return (0);
	while (rd != 0)
	{
		rd = read(fd, bf, BUFFER_SIZE);
		if (rd == -1)
			return (0);
		bf[rd] = '\0';
		printf("read %d bytes found %s\n" , rd, bf);
		if (strchr(bf, '\n'))
		{
			printf("found next line\n");
			return (s);
		}
		s = ft_strjoin(s, bf);
	}
	return (s);
}

int	main(void)
{
	int	fd;

	fd = open("gnl_tester/files/multiple_line_with_nl", O_RDONLY);
	printf("the read line is %s\n", get_next_line(fd));
	printf("the read line is %s\n", get_next_line(fd));
	close(fd);
	return (0);
}
