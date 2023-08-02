/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:22:37 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/02 11:23:41 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(int *pipe_fd, int pid, char **env, t_data *data)
{
	int	code;

	code = 1;
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(data->infile, STDIN_FILENO) != 1 && \
			dup2(pipe_fd[1], STDOUT_FILENO) != -1)
		{
			execve(data->cmd_paths[0], data->cmd_args[0], env);
			code = 127;
		}
		close(pipe_fd[1]);
		failure_exit(data, code);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) != -1 && \
	dup2(data->outfile, STDOUT_FILENO) != -1)
	{
		execve(data->cmd_paths[1], data->cmd_args[1], env);
		code = 127;
	}
	close(pipe_fd[0]);
	failure_exit(data, code);
}

void	exec_cmd(t_data *data, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		failure_exit(data, 1);
	pid = fork();
	if (pid == -1)
		failure_exit(data, 1);
	if (pid == 0)
	{
		if (data->infile >= 0)
			exec(fd, 0, env, data);
	}
	exec(fd, 1, env, data);
}