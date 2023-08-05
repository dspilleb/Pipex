/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:22:37 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/05 12:57:52 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(int *pipe_fd, int pid, char **env, t_data *data)
{
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(data->infile, STDIN_FILENO) != 1 && \
			dup2(pipe_fd[1], STDOUT_FILENO) != -1)
		{
			execve(data->cmd_paths[0], data->cmd_args[0], env);
			failure_exit(data, "command not found", 127);
		}
		close(pipe_fd[1]);
		failure_exit(data, "DUP2", 1);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) != -1 && \
	dup2(data->outfile, STDOUT_FILENO) != -1)
	{
		execve(data->cmd_paths[1], data->cmd_args[1], env);
		failure_exit(data, "command not found", 127);
	}
	close(pipe_fd[0]);
	failure_exit(data, "DUP2", 1);
}

void	fork_exec(t_data *data, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		failure_exit(data, "Pipe fail", 1);
	pid = fork();
	if (pid == -1)
		failure_exit(data, "Fork fail", 1);
	if (pid == 0)
	{
		if (data->infile < 0)
			exit(1);
		exec(fd, 0, env, data);
	}
	exec(fd, 1, env, data);
}
