/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:02:54 by dspilleb          #+#    #+#             */
/*   Updated: 2023/07/12 16:20:48 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	main(int ac, char **av, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;
	int		pid;
	int		fd[2];
	int		fd2;
	int	i = 0;

	if(ac != 4)
		return (0);
	pipe(fd);
	pid = fork();
	if (pid == -1)
		printf("Error");
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close (fd[0]);
		close (fd[1]);
		cmd_path = find_command_path(envp[12], av[2]);
		cmd_args = create_command_arg(av[2]);
		fd2 = open(av[1], O_RDWR);
		dup2(fd2, STDIN_FILENO);
		execve(cmd_path, cmd_args, NULL);
	}
	else
	{
		i = -1;
		fd2 = open(av[3], O_RDWR);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		
		close(fd[0]);
		wait(NULL);
	}
	return (0);
}
