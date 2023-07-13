/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:07:07 by dspilleb          #+#    #+#             */
/*   Updated: 2023/07/13 19:22:58 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "My_Libft/libft.h"

typedef struct pipex_data
{
	char	***cmd_args;
	char	**cmd_paths;
	int			cmd_count;
	int			total_cmds;
}	t_data;

void	free_matrix(char **arr);
char	*create_command_path(char *env_path, char *command);
char	*find_command_path(char *all_paths, char *command);
char	*find_env_path(char **envp);
void	set_cmds(t_data *data, int ac, char **av, char **envp);
int		exec_cmd(t_data *data, char **av);
#endif