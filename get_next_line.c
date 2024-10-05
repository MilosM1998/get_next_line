/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilicev <mmilicev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:40:49 by mmilicev          #+#    #+#             */
/*   Updated: 2024/10/05 11:49:56 by mmilicev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *refresh_buff(char *buffer)
{
    char    *new_buff;
    int     i;
    int     k;
    
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (!buffer[i])
    {
        free(buffer);
        return (NULL);
    }
    new_buff = malloc(ft_strlen(buffer) - i + 1);
    if (!new_buff)
        return (NULL);
    i++;
    k = 0;
    while(buffer[i])
        new_buff[k++] = buffer[i++];
    new_buff[k] = '\0';
    free(buffer);
    return (new_buff);
}

static char *take_line(char *buffer)
{
    char *new_line;
    int i;

    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    new_line = malloc(sizeof(char) * (i + 2));
    if (!new_line)
        return (NULL);
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        new_line[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
        new_line[i++] = '\n';
    new_line[i] = '\0';
    return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
    char        *tmp_buff;
    int         readed;
    
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp_buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp_buff)
		return (NULL);
    if (!buffer)
        buffer = ft_strdup("");
    while (!ft_strchr(buffer, '\n'))
    {
        readed = read(fd, tmp_buff, BUFFER_SIZE);
        if (readed == -1)
        {
            free(tmp_buff);
            free(buffer);
            return (NULL);
        }
        if (readed == 0)
            break;
        tmp_buff[readed] = '\0';
        char *old = buffer;
        buffer = ft_strjoin(buffer, tmp_buff);
        free(old);
    }
    free(tmp_buff);
    if (buffer[0] == '\0')
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    line = take_line(buffer);
    buffer = refresh_buff(buffer);
    return (line);
}

#include <fcntl.h>    // Za funkciju open()
#include <stdio.h>     // Za funkciju printf() i perror()
#include <stdlib.h>    // Za funkciju exit()
#include "get_next_line.h"  // Uključi svoj header za get_next_line

int main(void)
{
    int     fd;
    char    *line;

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



