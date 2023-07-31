/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:27:42 by dspilleb          #+#    #+#             */
/*   Updated: 2023/07/31 17:36:07 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_files(char **av, t_data *data)
{
	data->infile = open(av[1], O_RDONLY);
	if (data->infile == -1)
		perror(av[1]);
	data->outfile = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->outfile < 0)
	{
		perror(av[4]);
		return (EXIT_FAILURE);
	}
	return (0);
}

void	init_data(t_data *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->status = 0;
	data->env_path = NULL;
}
