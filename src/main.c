/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:31:32 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/03/28 18:19:11 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error(char *str, int errnum)
{
	if (errnum == 0)
		perror(0);
	else if (errnum == 1)
		ft_printf("command not found\n");
	else if (errnum == 99)
	{
		ft_printf("Error\n%s\n", str);
		exit (1);
	}
}

char **ft_check_path(char **envp)
{
	int		i;
	char	**path;
	char 	*temp;

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

char	*ft_get_path(char **path, char **cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], cmd[0]);
		if (!access(temp, F_OK))
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

void	ft_start_child(t_pipex *file, int *pipe_fd, char **envp)
{
	dup2(file->file_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(file->path, file->cmd, envp);
}

void	ft_end_child(t_pipex *file, int *pipe_fd, char **envp)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(file->file_fd, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(file->path, file->cmd, envp);
}

char *quotes(char *str)
{
	int 	len;

	len = 0;
	while (str[len])
		len++;
	if (str[0] == '"' && str[len - 1] == '"') {
		str[len - 1] = '\0';
		return (str + 1);
	}
	return (str);
}

void	ft_init_fork(char **path, char *av_cmd, t_pipex *file)
{
	int 	i;

	file->cmd = ft_split(av_cmd, ' ');
	i = 0;
	while (file->cmd[++i])
		file->cmd[i] = quotes(file->cmd[i]);
	file->path = ft_get_path(path, file->cmd);
	if (!file->path)
		ft_error(0, 1);
	else
	{
		file->pid = fork();
		if (file->pid == -1)
			ft_error(0, 2);
	}
}

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return;
	while (str[i])
		i++;
	while (str[--i])
		free(str[i]);
	free(str);
}

void	ft_free_close(t_pipex *infile, t_pipex *outfile)
{
	if (infile->cmd)
		ft_free_array(infile->cmd);
	if (infile->path)
		free(infile->path);
	if (infile->file_fd)
		close(infile->file_fd);
	if (outfile->cmd)
		ft_free_array(outfile->cmd);
	if (outfile->path)
		free(outfile->path);
	if (outfile->file_fd)
		close(outfile->file_fd);
}

int	main(int ac, char **av, char **envp)
{
	char	**path;
	int 	pipe_fd[2];
	t_pipex infile;
	t_pipex	outfile;

	if (ac == 5)
	{
		outfile.file_fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (outfile.file_fd == -1)
			ft_error(0,0);
		infile.file_fd = open(av[1], O_RDONLY);
		if (infile.file_fd == -1)
			ft_error(0,0);
		path = ft_check_path(envp);
		if (pipe(pipe_fd) == -1)
			ft_error(0,0);
		ft_init_fork(path, av[2], &infile);
		if (infile.pid == 0)
			ft_start_child(&infile, pipe_fd, envp);
		ft_init_fork(path, av[3], &outfile);
		if (outfile.pid == 0)
			ft_end_child(&outfile, pipe_fd, envp);
	}
	return (0);
}
