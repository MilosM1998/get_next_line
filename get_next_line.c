/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilicev <mmilicev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:40:49 by mmilicev          #+#    #+#             */
/*   Updated: 2024/10/07 14:31:51 by mmilicev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buffer, char *buff, int readed)
{
	char	*temp;

	while (!(ft_strchr(buffer, '\n')) && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
			return (NULL);
		if (readed == 0)
			break ;
		buff[readed] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, buff);
		free(temp);
		if (!buffer)
		{
			free(buff);
			return (NULL);
		}
	}
	return (buffer);
}

static char	*allocate_line(int fd, char *buffer)
{
	char	*buff;
	int		readed;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed = 1;
	buffer = read_line(fd, buffer, buff, readed);
	free(buff);
	return (buffer);
}

static char	*find_line(char *buffer)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	new_line = malloc(sizeof(char) * (i + 2));
	if (!new_line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		new_line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

char	*refresh_buff(char *buffer)
{
	int		i;
	int		j;
	char	*new_buff;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	new_buff = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!new_buff)
		return (NULL);
	j = 0;
	while (buffer[i])
		new_buff[j++] = buffer[i++];
	new_buff[j] = '\0';
	free(buffer);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (!buffer)
		buffer = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = allocate_line(fd, buffer);
	if (!buffer || *buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = find_line(buffer);
	buffer = refresh_buff(buffer);
	if (buffer && *buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
 */