/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:13:19 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/10 10:13:22 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**ft_get_env_path(char **envp)
{
	int		i;
	char	**path;
	char	*temp;

	i = 0;
	path = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = temp;
		i++;
	}
	return (path);
}

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		i++;
	while (array[i])
	{
		free(array[i]);
		i--;
	}
	free(array);
}

void	ft_close_all(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	ft_free_array(pipex->path);
	free(pipex->cmd1.path);
	ft_free_array(pipex->cmd1.args);
	free(pipex->cmd2.path);
	ft_free_array(pipex->cmd2.args);
}
