/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilicev <mmilicev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:40:49 by mmilicev          #+#    #+#             */
/*   Updated: 2024/10/04 19:31:58 by mmilicev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_line(char *buffer)
{
	char	*new_line;
    int     len;
    len = 0;
    while(buffer[len] <= BUFFER_SIZE || buffer[len] == '\n')
        len++;
    new_line = malloc(sizeof(char) * len + 1); 
    if (!new_line)
    {
        free(new_line);
        return NULL;
    }
    while(len-- >= 0)
    {
        if (buffer[len] != '\n')
        {   
            new_line[len] = '\n';
            new_line[len - 1] = buffer[len - 1];
            len--;
        }
        else
        {   
            new_line[len] = buffer[len];
            len--;
        }
    }
    return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read(fd, buffer, BUFFER_SIZE);
	if (!buffer)
		return (NULL);
    buffer = 0;
    line = find_line(buffer);
    return (line);
}

#include <fcntl.h>    // Za funkciju open()
#include <stdio.h>     // Za funkciju printf() i perror()
#include <stdlib.h>    // Za funkciju exit()
#include "get_next_line.h"  // Uključi svoj header za get_next_line

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    // Provera da li je korisnik naveo fajl kao argument
    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return (1);
    }

    // Otvaranje fajla u read-only modu
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    // Petlja koja poziva get_next_line i ispisuje svaku liniju dok se ne dođe do kraja fajla
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);  // Ispisuje pročitanu liniju
        free(line);          // Oslobađanje memorije koju je alocirala get_next_line
    }

    // Zatvaranje fajla
    if (close(fd) == -1)
    {
        perror("Error closing file");
        return (1);
    }

    return (0);
}

