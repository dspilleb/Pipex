/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:27:42 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/04 17:06:01 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	init_files(int ac, char **av, t_data *data)
{
	if (is_equal(av[1], "here_doc") == 0)
	{
		data->here_doc = 1;
		data->outfile = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	else
	{
		data->infile = open(av[1], O_RDONLY);
		if (data->infile == -1)
			perror(av[1]);
		data->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
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
	data->exec_count = -1;
	data->cmd_count = 0;
	data->here_doc = 0;
	data->pid = NULL;
	data->path = NULL;
	data->cmd_args = NULL;
	data->cmd_paths = NULL;
}

void	init_pid_storage(t_data *data)
{
	int	i;

	i = -1;
	if (!data->cmd_count)
		return ;
	data->pid = malloc(sizeof(int) * (data->cmd_count));
	if (!data->pid)
		failure_exit(data, "failed malloc", 1);
	while (++i < data->cmd_count)
		data->pid[i] = 0;
}
