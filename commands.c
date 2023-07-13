/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:42:11 by dspilleb          #+#    #+#             */
/*   Updated: 2023/07/12 16:32:21 by dspilleb         ###   ########.fr       */
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

char	**create_command_arg(char *command)
{
	char	**arr;
	int		i;

	i = 0;
	if (!command)
		return (NULL);
	arr = ft_split(command, ' ');
	if (!arr)
		return (NULL);
	return (arr);
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
