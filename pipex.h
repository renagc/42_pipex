/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:53 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/03/28 18:20:25 by rgomes-c         ###   ########.fr       */
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
# include "ft_printf/ft_printf.h"

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

typedef struct s_pipex
{
	int		file_fd;
	char	*path;
	char	**cmd;
	pid_t	pid;
}t_pipex;

// -----------------------------  FUNCTIONS --------------------------------- //

//utils.c
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);

//split.c
size_t	ft_strlen(char const *s);
char	**ft_split(char const *s, char c);

#endif