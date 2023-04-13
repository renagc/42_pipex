/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:13:19 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/13 14:31:02 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**ft_get_env_path_array(char **envp)
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

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	ft_close_all(t_pipex *pipex)
{
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd)
		close(pipex->outfile_fd);
	if (pipex->path)
		ft_free_array(pipex->path);
	if (pipex->cmd1.path)
		free(pipex->cmd1.path);
	if (pipex->cmd1.args)
		ft_free_array(pipex->cmd1.args);
	if (pipex->cmd2.path)
		free(pipex->cmd2.path);
	if (pipex->cmd2.args)
		ft_free_array(pipex->cmd2.args);
}
