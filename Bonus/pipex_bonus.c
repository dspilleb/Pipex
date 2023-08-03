/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:02:54 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/03 15:16:13 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	errno = 0;
	if (!env || ac < 5 || (is_equal(av[1], "here_doc") == 0 && ac < 6))
	{
		ft_putstr_fd("usage 1 : file1 cmd1 cmd2 file2\n usage 2 : \
		here_doc LIMITER cmd cmd1 file\n", 2);
		return (EXIT_FAILURE);
	}
	init_data(&data);
	data.status = init_files(ac, av, &data);
	if (data.status != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	data.status = set_cmds(&data, ac, av, env);
	if (data.status == 0)
	{
		if (!data.here_doc && data.infile != -1)
			dup2(data.infile, STDIN_FILENO);
		else if (data.here_doc)
			here_doc_stdin(&data, av[2]);
		while (++data.exec_count < data.cmd_count)
			fork_exec(&data, env);
	}
	free_cmds(&data);
	return (data.status);
}
