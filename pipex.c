/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:02:54 by dspilleb          #+#    #+#             */
/*   Updated: 2023/07/13 19:32:39 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	exec_cmd(t_data *data, char **av)
{
	char buf;
	int	fd2;
	int fd[2];
	pid_t pid;

	pipe(fd);
	printf("hey\n");
	pid = fork();
	if (pid == -1)
	{
		perror("pipe");
        exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if(data->cmd_count == 0)
			fd2 = open(av[1], O_RDONLY);
		dup2(fd2, STDIN_FILENO);
		close(fd[0]);
		dup2(STDOUT_FILENO, fd[1]);
		data->cmd_count++;
		execve(data->cmd_paths[data->cmd_count], data->cmd_args[data->cmd_count], NULL);
		close(fd[1]);
	}
	else
	{
		printf("aled\n");
		wait(NULL);
		close(fd[1]);	
        while (read(fd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
		close(fd[0]);
	}
	return (0);
}

char *find_env_path(char **envp)
{
	while(*envp)
	{
		if (ft_strnstr(*envp, "PATH", ft_strlen(*envp)))
			return (strdup(*envp));
		envp++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_data data;

	if (ac < 5)
	{
		printf("non");
		return (1);
	}
	if (access(av[1], R_OK) != 0)
	{
		printf("erreur");
		return (1);
	}
	data.cmd_count = 0;
	data.total_cmds = 0;
	set_cmds(&data, ac, av, envp);
	printf("%d", data.total_cmds);
	while (data.cmd_count < data.total_cmds)
	{
		printf("oui");
		exec_cmd(&data, av);
	}
	return (0);
}
