/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:42:11 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/04 17:06:01 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_envp(char **envp)
{
	while (envp && *envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			return (*envp + 5);
		envp++;
	}
	ft_putstr_fd("No PATH", 2);
	return (NULL);
}

char	*create_command_path(char *path, char *command)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin("/", command);
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(path, tmp);
	free(tmp);
	return (full_path);
}

char	*find_command_path(t_data *data, char *all_paths, char *command)
{
	int		i;
	char	**arr;
	char	*full_path;

	i = -1;
	if (!command || !ft_strlen(command))
		return (NULL);
	arr = ft_split(all_paths, ':');
	if (!arr)
		failure_exit(data, "Malloc fail", 1);
	while (arr && arr[++i])
	{
		full_path = create_command_path(arr[i], command);
		if (full_path && access(full_path, F_OK | X_OK) == 0)
		{
			free_matrix(arr);
			return (full_path);
		}
		if (full_path)
			free(full_path);
	}
	if (arr)
		free_matrix(arr);
	return (ft_strdup(command));
}

int	set_cmds(t_data *data, int ac, char **av, char **envp)
{
	int		i;
	int		tmp;
	char	**tmp_arr;

	tmp = 3;
	if (data->here_doc == 1)
		tmp++;
	i = -1;
	data->path = find_envp(envp);
	if (!data->path)
		return (EXIT_FAILURE);
	data->cmd_paths = malloc(sizeof(char *) * (ac - tmp));
	data->cmd_args = malloc(sizeof(char **) * (ac - tmp));
	if (!data->cmd_paths || ! data->cmd_args)
		return (EXIT_FAILURE);
	while (++i < ac - tmp)
	{
		tmp_arr = ft_split(av[i + tmp - 1], ' ');
		if (!tmp_arr)
			return (EXIT_FAILURE);
		data->cmd_paths[i] = find_command_path(data, data->path, tmp_arr[0]);
		data->cmd_args[i] = tmp_arr;
		data->cmd_count++;
	}
	return (EXIT_SUCCESS);
}

void	free_cmds(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd_paths && ++i < data->cmd_count)
		free(data->cmd_paths[i]);
	i = -1;
	while (data->cmd_args && ++i < data->cmd_count)
		free_matrix(data->cmd_args[i]);
	free(data->cmd_args);
	free(data->cmd_paths);
	free(data->pid);
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
}
