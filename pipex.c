/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:02:54 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/01 15:09:17 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	failure_exit(t_data *data, int code)
{
	free_cmds(data);
	if (code == 127)
		perror("command not found");
	else
		perror("error");
	exit(code);
}

void	exec(int *fd, int nb, char **env, t_data *data)
{
	int	code;

	code = 1;
	if (nb == 0)
	{
		close(fd[0]);
		if (dup2(data->infile, STDIN_FILENO) != 1 && \
			dup2(fd[1], STDOUT_FILENO) != -1)
		{
			execve(data->cmd_paths[0], data->cmd_args[0], env);
			code = 127;
		}
		close(fd[1]);
		failure_exit(data, code);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) != -1 && \
	dup2(data->outfile, STDOUT_FILENO) != -1)
	{
		execve(data->cmd_paths[1], data->cmd_args[1], env);
		code = 127;
	}
	close(fd[0]);
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
		if (data->infile < 0)
			return ;
		exec(fd, 0, env, data);
		close(fd[1]);
	}
	exec(fd, 1, env, data);
	close(fd[0]);
}

char	*find_env_path(char **envp)
{
	while (envp && *envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 5)
	{
		write(2, "usage : file1 cmd1 cmd2 file2\n", 30);
		return (EXIT_FAILURE);
	}
	if (!env)
	{
		write(2, "no environment\n", 15);
		return (EXIT_FAILURE);
	}
	init_data(&data);
	data.status = init_files(av, &data);
	if (data.status != 0)
		return (EXIT_FAILURE);
	data.status = set_cmds(&data, av, env);
	if (data.status == 0)
		exec_cmd(&data, env);
	free_cmds(&data);
	return (data.status);
}
