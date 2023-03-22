/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:53 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/03/22 16:11:14 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// ------------------------------- INCLUDES --------------------------------- //

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "ft_printf/ft_printf.h"

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

typedef struct s_struct
{
	int		infile;
	int		outfile;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1;
	char	**cmd2;
	char	*path;
	int		pipe_fd[2];
	pid_t	pid;
}t_struct;


// -----------------------------  FUNCTIONS --------------------------------- //

//utils.c
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_array(char ***str);

// errors.c
void	ft_basic_errors(int ac, char **av, t_struct *pipex);

//split
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);

#endif