/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:07:07 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/05 12:38:24 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../My_Libft/libft.h"

typedef struct pipex_data
{
	char	***cmd_args;
	char	**cmd_paths;
	char	*path;
	int		infile;
	int		outfile;
	int		status;
	int		cmd_count;
}	t_data;

void	free_matrix(char **arr);
void	failure_exit(t_data *data, char *str, int code);

char	*create_command_path(char *envp, char *command);
char	*find_command_path(t_data *data, char *all_paths, char *command);
char	*find_envp(char **envp);
int		set_cmds(t_data *data, char **av, char **envp);
void	free_cmds(t_data *data);

void	exec(int *fd, int nb, char **env, t_data *data);
void	fork_exec(t_data *data, char **env);

int		init_files(char **av, t_data *data);
void	init_data(t_data *data);

#endif