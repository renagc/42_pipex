/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:32:49 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/03/28 18:18:31 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_basic_errors(int ac, char **av, t_struct *pipex)
{
	if (ac != 5)
	{
		perror("Error\n");
		exit(0);
	}
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		ft_printf("Error\n");
		exit(0);
	}
	pipex->outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (pipex->outfile == -1)
	{
		ft_printf("Error\n");
		exit(0);
	}
}
