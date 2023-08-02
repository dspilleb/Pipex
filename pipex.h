/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:07:07 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/02 11:32:50 by dspilleb         ###   ########.fr       */
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
# include "My_Libft/libft.h"

typedef struct pipex_data
{
	char	***cmd_args;
	char	**cmd_paths;
	char	*env_path;
	int		infile;
	int		outfile;
	int		status;
	int		cmd_count;
}	t_data;

void	free_matrix(char **arr);
char	*create_command_path(char *env_path, char *command);
char	*find_command_path(char *all_paths, char *command);
char	*find_env_path(char **envp);
int		set_cmds(t_data *data, char **av, char **envp);
void	fork_exec(t_data *data, char **env);
void	free_cmds(t_data *data);
int		init_files(char **av, t_data *data);
void	init_data(t_data *data);
void	failure_exit(t_data *data, int code);
void	exec(int *fd, int nb, char **env, t_data *data);
void	fork_exec(t_data *data, char **env);
#endif