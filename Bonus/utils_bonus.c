/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:22:20 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/05 12:21:44 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	failure_exit(t_data *data, char *str, int code)
{
	free_cmds(data);
	if (str)
		perror(str);
	exit(code);
}

int	is_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	wait_all_process(t_data *data)
{
	int	status;
	int	j;

	j = -1;
	while (++j < data->cmd_count)
	{
		waitpid(data->pid[j], &status, 0);
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
	}
}
