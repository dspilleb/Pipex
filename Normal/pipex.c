/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:02:54 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/05 12:53:16 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 5)
	{
		ft_putstr_fd("usage : file1 cmd1 cmd2 file2\n", 2);
		return (EXIT_FAILURE);
	}
	if (!env)
	{
		ft_putstr_fd("no environment\n", 2);
		return (EXIT_FAILURE);
	}
	init_data(&data);
	data.status = init_files(av, &data);
	if (data.status != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	data.status = set_cmds(&data, av, env);
	if (data.status == EXIT_SUCCESS)
		fork_exec(&data, env);
	free_cmds(&data);
	return (data.status);
}
