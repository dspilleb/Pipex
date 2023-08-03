/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:07:07 by dspilleb          #+#    #+#             */
/*   Updated: 2023/08/03 11:10:09 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../My_Libft/libft.h"
# include "../GNL/get_next_line_bonus.h"

typedef struct pipex_data
{
	char	***cmd_args;
	char	**cmd_paths;
	char	*env_path;
	int		infile;
	int		outfile;
	int		here_doc;
	int		status;
	int		cmd_count;
	int		exec_count;
}	t_data;

void	free_matrix(char **arr);
void	failure_exit(t_data *data, char *str, int code);
int		is_equal(char *s1, char *s2);

char	*create_command_path(char *env_path, char *command);
char	*find_command_path(char *all_paths, char *command);
char	*find_env_path(char **envp);
int		set_cmds(t_data *data, int ac, char **av, char **envp);
void	free_cmds(t_data *data);

void	exec(int *fd, int nb, char **env, t_data *data);
void	fork_exec(t_data *data, char **env);
void	read_here_doc(char *stop, int *fd);
void	here_doc_stdin(t_data *data, char *stop);

int		init_files(int ac, char **av, t_data *data);
void	init_data(t_data *data);

#endif