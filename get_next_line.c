/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmouttap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:24:14 by lmouttap          #+#    #+#             */
/*   Updated: 2024/12/10 17:33:06 by lmouttap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

void	set_it_free(char *it)
{
	free(it);
	it = NULL;
}

char	*store_stash(char *line)
{
	char	*dest;
	int		i;

	i = ft_strchr(line, '\n') + 1;
	if (i == 0)
		return (NULL);
	dest = ft_strdup(&line[i]);
	while (line[i])
	{
		line[i] = 0;
		i++;
	}
	if (dest && *dest == '\0')
	{
		free(dest);
		dest = NULL;
	}
	return (dest);
}

char	*create_line(int fd, char *stash, char *buf)
{
	char	*temp;
	int		bytes_read;

	temp = NULL;
	bytes_read = 1;
	if (stash != NULL)
	{
		temp = ft_strdup(stash);
		set_it_free(stash);
	}
	while (!temp || (ft_strchr(temp, '\n') == -1 && bytes_read > 0))
	{
		if (temp)
		{
			stash = ft_strdup(temp);
			set_it_free(temp);
		}
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		temp = ft_strjoin(stash, buf);
		set_it_free(stash);
	}
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
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		set_it_free(buf);
		// set_it_free(stash); --> double free detected in tcache 2
		return (NULL);
	}
	line = create_line(fd, stash, buf);
	if (!line || (line && *line == '\0'))
	{
		set_it_free(buf);
		set_it_free(line);
		set_it_free(stash);
		return (NULL);
	}
	stash = store_stash(line);
	if (!stash || (stash && *stash == '\0'))
		set_it_free(stash);
	return (set_it_free(buf), line);
}

// int	main(void)
// {
// 	char	*path;
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	path = "../text.txt";
// 	fd = open(path, O_RDONLY);
// 	while (i < 11)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			printf("\n");
// 		printf("call_%d: %s", i, line);
// 		set_it_free(line);
// 		i++;
// 	}
// 	return (0);
// }
