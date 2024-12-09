/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmouttap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:25:05 by lmouttap          #+#    #+#             */
/*   Updated: 2024/11/30 16:30:32 by lmouttap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

// TO REMOVE -----------------------------------------------------------------
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
// TO REMOVE -----------------------------------------------------------------

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

int	    ft_strchr(char *str, char a);
int     ft_strlen(char *str);
char    *ft_strdup(char *str);
char    *ft_strjoin(char *s1, char *s2);
// char    *ft_substr(char *s, unsigned int start, unsigned int len);
char	*create_line(int fd, char *stash, char *buf);
char	*store_stash(char *line);
char	*get_next_line(int fd);

#endif
