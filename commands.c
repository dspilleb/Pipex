/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:42:11 by dspilleb          #+#    #+#             */
/*   Updated: 2023/07/13 19:34:56 by dspilleb         ###   ########.fr       */
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

char	*create_command_path(char *env_path, char *command)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin("/", command);
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(env_path, tmp);
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
		return (NULL);
	arr = ft_split(all_paths, ':');
	if (!arr)
		return (NULL);
	while (arr[++i])
	{
		full_path = create_command_path(arr[i], command);
		if (!full_path)
			break ;
		else if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	free_matrix(arr);
	return (NULL);
}

void set_cmds(t_data *data, int ac, char **av, char **envp)
{
	int	i;
	char **tmp_arr;
	char *env_path;

	i = 1;
	data->total_cmds = 0;
	printf("set cmds\n");
	env_path = find_env_path(envp);
	if (!env_path)
		return ;
	data->cmd_paths = malloc(sizeof(char *) * (ac - 2));
	data->cmd_args = malloc(sizeof(char **) * (ac - 2));
	while (++i < ac - 1)
	{
		tmp_arr = ft_split(av[i], ' ');
		if (!tmp_arr)
			return ;
		data->cmd_paths[i - 2] = find_command_path(env_path, tmp_arr[0]);
		data->cmd_args[i - 2] = ft_split(av[i], ' ');
		data->total_cmds++;
		free_matrix(tmp_arr);
		printf("set cmds2\n");
	}
	data->cmd_paths[i - 2] = NULL;
	data->cmd_args[i - 2] =  NULL;
}
