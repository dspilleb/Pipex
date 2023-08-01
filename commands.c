/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:42:11 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/01 14:50:41 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrix(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
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

char	*find_command_path(char *all_paths, char *command)
{
	int		i;
	char	**arr;
	char	*full_path;

	i = -1;
	if (!command || !ft_strlen(command))
		return (strdup(""));
	arr = ft_split(all_paths, ':');
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
	return (strdup(command));
}

int	set_cmds(t_data *data, char **av, char **envp)
{
	int		i;
	char	**tmp_arr;

	i = -1;
	data->env_path = find_env_path(envp);
	if (!data->env_path || data->status != 0)
		return (EXIT_FAILURE);
	data->cmd_paths = malloc(sizeof(char *) * (2));
	data->cmd_args = malloc(sizeof(char **) * (2));
	if (!data->cmd_paths || ! data->cmd_args)
		return (EXIT_FAILURE);
	while (++i < 2)
	{
		tmp_arr = ft_split(av[i + 2], ' ');
		if (!tmp_arr)
			return (EXIT_FAILURE);
		data->cmd_paths[i] = find_command_path(data->env_path, tmp_arr[0]);
		data->cmd_args[i] = ft_split(av[i + 2], ' ');
		free_matrix(tmp_arr);
		if (!data->cmd_args[i])
			return (EXIT_FAILURE);
		else
			data->arg_count++;
	}
	return (EXIT_SUCCESS);
}

void	free_cmds(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd_paths && ++i < data->arg_count)
	{
		if (data->cmd_paths[i])
			free(data->cmd_paths[i]);
	}
	i = -1;
	while (data->cmd_args && ++i < data->arg_count)
		free_matrix(data->cmd_args[i]);
	if (data->cmd_args)
		free(data->cmd_args);
	if (data->cmd_paths)
		free(data->cmd_paths);
}
