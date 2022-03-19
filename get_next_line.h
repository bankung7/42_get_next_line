/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:55:14 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/19 15:02:49 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GNL_H
# define GNL_H

#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(char const *s);
char	*ft_strdup(char const *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
