/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 12:19:06 by jocorral          #+#    #+#             */
/*   Updated: 2026/09/30 13:00:36 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

size_t	detect_next_line(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	return (i);
}

int	check_in_stash(char **stash, size_t *sz, char *buf, size_t r)
{
	char	*new;
	size_t	i;

	if (sz[0] + r + 1 > sz[1])
	{
		while (sz[0] + r + 1 > sz[1])
			sz[1] *= 2;
		new = malloc(sz[1]);
		if (!new)
			return (-1);
		i = -1;
		while (++i < sz[0])
			new[i] = (*stash)[i];
		free(*stash);
		*stash = new;
	}
	i = -1;
	while (++i < r)
		(*stash)[sz[0] + i] = buf[i];
	(*stash)[sz[0] + r] = '\0';
	i = sz[0];
	sz[0] += r;
	return ((*stash)[i + detect_next_line(*stash + i)] == '\n');
}

int	read_to_stash(int fd, char **stash)
{
	char	*buf;
	ssize_t	r;
	int		status;
	size_t	sz[2];

	if (*stash && (*stash)[detect_next_line(*stash)] == '\n')
		return (0);
	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (-1);
	sz[0] = ft_strlen(*stash);
	sz[1] = sz[0] + 1;
	status = 0;
	r = 1;
	while (status == 0 && r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r > 0)
			status = check_in_stash(stash, sz, buf, r);
	}
	free(buf);
	if (r < 0 || status < 0)
		return (-1);
	return (0);
}
