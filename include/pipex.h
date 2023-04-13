/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:53 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/13 14:30:44 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// ------------------------------- INCLUDES --------------------------------- //

# include <stdio.h>
# include <string.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "ft_printf.h"
# include "libft.h"

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

typedef struct s_cmd
{
	char				*path;
	char				**args;
}t_cmd;

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	char	**path;
	t_cmd	cmd1;
	t_cmd	cmd2;
}t_pipex;

// -----------------------------  FUNCTIONS --------------------------------- //

//utils.c
void	ft_free_array(char **array);
void	ft_close_all(t_pipex *pipex);
char	**ft_get_env_path_array(char **envp);

#endif