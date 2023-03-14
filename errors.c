/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:32:49 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/03/14 19:54:58 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_check_file(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	return (1);
}

void	ft_errors(int ac, char **av)
{
	if (ac > 5)
		perror("Too much arguments");
	if (!ft_check_file(av[1]) || !ft_check_file(av[4]))
		perror(av[1]);
	exit(0);
}
