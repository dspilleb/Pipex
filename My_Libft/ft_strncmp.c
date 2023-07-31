/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:49:31 by dan               #+#    #+#             */
/*   Updated: 2023/07/31 13:24:01 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	result = 0;
	i = 0;
	while (s1[i] && i < n && s1[i] == s2[i])
		i++;
	if (i != n)
		result = ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (result);
}
