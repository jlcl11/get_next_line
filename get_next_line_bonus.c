/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 20:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/02 16:47:16 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
//#include <stdio.h>

static char	*split_stash(char **stash)
{
	char	*line;
	char	*rest;
	char	*nl;
	size_t	len;

	len = ft_strlen_bonus(*stash);
	nl = ft_strchr_bonus(*stash, '\n');
	if (nl)
		len = nl - *stash + 1;
	line = ft_extract_bonus(*stash, 0, len);
	rest = NULL;
	if (line && (*stash)[len])
		rest = ft_extract_bonus(*stash, len, ft_strlen_bonus(*stash) - len);
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
	static char	*stash[MAX_FD];

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_to_stash_bonus(fd, stash[fd]);
	if (!stash[fd] || !*stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	return (split_stash(&stash[fd]));
}

/* main 3 (bonus): alterna lineas de dos fd (gargola.txt y mayorqueyo.txt) */

/*int	main(void)
{
int		fd1;
int		fd2;
char	*l1;
char	*l2;

fd1 = open("gargola.txt", O_RDONLY);
fd2 = open("enlacama.txt", O_RDONLY);
if (fd1 < 0 || fd2 < 0)
{
perror("open");
return (1);
}
l1 = get_next_line(fd1);
l2 = get_next_line(fd2);
while (l1 || l2)
{
if (l1)
printf("[fd %d] %s", fd1, l1);
if (l2)
printf("[fd %d] %s", fd2, l2);
free(l1);
free(l2);
l1 = get_next_line(fd1);
l2 = get_next_line(fd2);
}
printf("\n--- fin (ambos fd devolvieron NULL) ---\n");
close(fd1);
close(fd2);
return (0);
}*/
