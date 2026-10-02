/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 20:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/01 20:00:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_bonus(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr_bonus(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return (s);
	return (NULL);
}

char	*ft_strjoin_free_bonus(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(ft_strlen_bonus(s1) + ft_strlen_bonus(s2) + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*ft_extract_bonus(char *s, size_t start, size_t len)
{
	char	*res;
	size_t	slen;
	size_t	i;

	slen = ft_strlen_bonus(s);
	if (start >= slen)
		return (NULL);
	if (len > slen - start)
		len = slen - start;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*read_to_stash_bonus(int fd, char *stash)
{
	char	*buf;
	ssize_t	r;

	buf = malloc(BUFFER_SIZE + 1);
	r = 1;
	if (!buf)
		r = -1;
	while (r > 0 && !ft_strchr_bonus(stash, '\n'))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r > 0)
		{
			buf[r] = '\0';
			stash = ft_strjoin_free_bonus(stash, buf);
			if (!stash)
				r = -1;
		}
	}
	free(buf);
	if (r < 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}
