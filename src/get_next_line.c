/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmouttap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:24:14 by lmouttap          #+#    #+#             */
/*   Updated: 2024/11/30 16:24:41 by lmouttap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*store_stash(char *line)
{
	char	*stash;
	int		i;

	i = ft_strchr(line, '\n');
	stash = ft_strdup(&line[i]);
	while (line[i])
	{
		line[i] = 0;
		i++;
	}
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	return (stash);
}

char	*create_line(int fd, char *stash, char *buf)
{
	char	*temp;
	char	*loop_temp;
	int		bytes_read;

	temp = NULL;
	loop_temp = NULL;
	bytes_read = 1;
	if (stash != NULL)
	{
		temp = ft_strdup(stash);
		free(stash);
	}
	while (!temp || (ft_strchr(temp, '\n') == -1 && bytes_read))
	{
		if (temp)
		{
			loop_temp = ft_strdup(temp);
			free(temp);
			temp = NULL;
		}
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		temp = ft_strjoin(loop_temp, buf);
		free(loop_temp);
		loop_temp = NULL;
	}
	// printf("stash: %s",stash);
	stash = store_stash(temp);
	if (!bytes_read && ft_strchr(temp, '\n') == -1)
		free(stash);
	// printf("stash: %s",stash);
	return (temp);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buf;
	static char		*stash;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buf);
		free(stash);
		return (NULL);
	}
	line = create_line(fd, stash, buf);

	// printf("stash: %s",stash);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	free(buf);
	return (line);
}


int	main(void)
{
	char	*path;
	int		fd;
	char	*line;

	path = "../text.txt";
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	printf("call_1: %s\n", line);
	free(line);
	// printf("call_2: %s\n", get_next_line(fd));
	// printf("call_3: %s\n", get_next_line(fd));
	// printf("call_4: %s\n", get_next_line(fd));
	// printf("call_5: %s\n", get_next_line(fd));
	// printf("call_6: %s\n", get_next_line(fd));
	// printf("call_7: %s\n", get_next_line(fd));
	// printf("call_8: %s\n", get_next_line(fd));
	// printf("call_9: %s\n", get_next_line(fd));
	// printf("call_d: %s\n", get_next_line(fd));
	return (0);
}
