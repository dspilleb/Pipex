/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:55:22 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/02 14:46:05 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# define FD_MAX 1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_strrchr(const char *s, int c);
char	*extract(char *stock);
char	*ft_cleaner(char *stock, char *line);
size_t	ft_strlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*free_join(char *stock, char *buffer);
size_t	ft_strlcpy(char *dest, char const *src, size_t size);

#endif