/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:27:42 by dspilleb          #+#    #+#             */
/*   Updated: 2023/07/31 12:20:55 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_files(char **av, t_data *data)
{
	data->infile = open(av[1], O_RDONLY);
	if (access(av[4], F_OK) == 0)
	{
		if (access(av[4], W_OK) == 0)
			data->outfile = open(av[4], O_WRONLY | O_TRUNC);
		else
			return (EXIT_FAILURE);
	}
	else
		data->outfile = open(av[4], O_CREAT | O_WRONLY, 0777);
	if (data->outfile < 0)
		return (EXIT_FAILURE);
	return (0);
}
