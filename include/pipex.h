/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:53 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/05 17:28:57 by rgomes-c         ###   ########.fr       */
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
# include "ft_printf.h"
# include "libft.h"

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


#endif