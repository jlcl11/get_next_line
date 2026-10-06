/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jocorral <jocorral@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/09/30 09:54:49 by jocorral         #+#    #+#              */
/*   Updated: 2026/10/06 15:59:37 by jocorral        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>

static char	*split_stash(char **stash)
{
	char	*line;
	char	*rest;
	char	*nl;
	size_t	len;

	len = ft_strlen(*stash);
	nl = ft_strchr(*stash, '\n');
	if (nl)
		len = nl - *stash + 1;
	line = ft_extract(*stash, 0, len);
	rest = NULL;
	if (line && (*stash)[len])
		rest = ft_extract(*stash, len, ft_strlen(*stash) - len);
	if (!line || ((*stash)[len] && !rest))
	{
		free(line);
		line = NULL;
	}
	free(*stash);
	*stash = rest;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (split_stash(&stash));
}

/* main 1 : lee de un archivo(gargola.txt) */

/*int	main(void)
{
int		fd;
char	*line;
int		n;

fd = open("gargola.txt", O_RDONLY);
if (fd < 0)
{
perror("open");
return (1);
}
n = 1;
line = get_next_line(fd);
while (line)
{
printf("[%d] %s", n++, line);
free(line);
line = get_next_line(fd);
}
printf("\n--- fin (get_next_line devolvio NULL) ---\n");
close(fd);
return (0);
}
*/

/* main 2: lee de la consola (stdin, fd = 0) */

/*int	main(void)
{
char	*line;

line = get_next_line(0);
while (line)
{
write(0, line, ft_strlen(line));
free(line);
line = get_next_line(0);
}
return (0);
}*/
