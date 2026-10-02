/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocorral <jocorral@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 20:00:00 by jocorral          #+#    #+#             */
/*   Updated: 2026/10/01 20:00:00 by jocorral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line_bonus(int fd);
size_t	ft_strlen_bonus(char *s);
char	*ft_strchr_bonus(char *s, int c);
char	*ft_strjoin_free_bonus(char *s1, char *s2);
char	*ft_extract_bonus(char *s, size_t start, size_t len);
char	*read_to_stash_bonus(int fd, char *stash);

#endif
