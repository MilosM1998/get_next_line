// don't forget header 

#include "get_next_line.h"
#include <stdlib.h>
char    *get_next_line(int fd)
{
    static char *buffer;
    char        *line;
    size_t       readen;
    int         i;

    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
        readen = read(fd, buffer, BUFFER_SIZE);
        if (readen <= 0) 
            return (NULL);
    while (readen)
    {

    }
    

}