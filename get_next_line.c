/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilicev <mmilicev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:40:49 by mmilicev          #+#    #+#             */
/*   Updated: 2024/10/06 13:29:30 by mmilicev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *temp_buff)
{
	char	*buff;
	int		readed;
    
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed = 1;
    if (!temp_buff)
    {
        temp_buff = ft_strdup("");
    }
	while (!ft_strchr(temp_buff, '\n') && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buff);
			return (NULL);
		}
        if (readed == 0)
        {
            free(buff);
            return (temp_buff); 
        }
		buff[readed] = '\0';
		temp_buff = ft_strjoin(temp_buff, buff);
	}
	free(buff);
	return (temp_buff);
}
char	*find_line(char *temp_buff)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!temp_buff)
		return (NULL);
	while (temp_buff[i] && temp_buff[i] != '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (temp_buff[i] && temp_buff[i] != '\n')
	{
		new_line[i] = temp_buff[i];
		i++;
	}
	if (temp_buff[i] == '\n')
		new_line[i] = '\n';
	new_line[i] = '\0';
	return (new_line);
}
char	*get_next_line(int fd)
{
	static char	*temp_buff = NULL;
	char		*line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
	    return (NULL);
    temp_buff = read_line(fd, temp_buff);
    if (!temp_buff)
    {
        free(temp_buff);
        temp_buff = NULL; 
        return (NULL);
    }
	line = find_line(temp_buff);
	temp_buff = refresh_buff(temp_buff);
	return (line);
}

#include <fcntl.h>    
#include <stdio.h>     
#include <stdlib.h>    

int	main(void)
{
	int		fd;
	char	*line;

	// Otvori fajl za testiranje (možeš zameniti putanju sa odgovarajućim fajlom)
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	// Testiraj get_next_line funkciju
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line); // Oslobodi memoriju svake linije nakon što je pročitaš
	}
	// Zatvori fajl kada završiš
	close(fd);
	return (0);
}



 