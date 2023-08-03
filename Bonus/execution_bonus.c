/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:22:37 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/03 11:45:04 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(int *pipe_fd, int pid, char **env, t_data *data)
{
	int	ret;

	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (data->exec_count == (data->cmd_count - 1))
			ret = dup2(data->outfile, STDOUT_FILENO);
		else 
			ret = dup2(pipe_fd[1], STDOUT_FILENO);
		if (ret != -1)
		{
			execve(data->cmd_paths[data->exec_count], \
			data->cmd_args[data->exec_count], env);
			failure_exit(data, "command not found", 127);
		}
		close(pipe_fd[1]);
		failure_exit(data, "Dup2", 1);
	}
}

void	fork_exec(t_data *data, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		failure_exit(data, "Pipe", 1);
	pid = fork();
	if (pid == -1)
		failure_exit(data, "Fork", 1);
	if (pid == 0)
	{
		if (data->infile >= 0 || data->here_doc)
			exec(fd, 0, env, data);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		failure_exit(data, "Dup2", 1);
}

void	here_doc_stdin(t_data *data, char *stop)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		failure_exit(data, "Pipe", 1);
	pid = fork();
	if (pid == -1)
		failure_exit(data, "Fork", 1);
	if (pid == 0)
	{
		read_here_doc(stop, fd);
	}
	else
	{
		wait(NULL);
		close (fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			failure_exit(data, "Dup2", 1);
	}
}

void	read_here_doc(char *stop, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit(1);
		if (ft_strncmp(line, stop, ft_strlen(stop)) == 0 \
			&& (ft_strlen(line) - 1) == ft_strlen(stop))
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}
