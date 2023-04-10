/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:31:32 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/05 17:29:21 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//vai ter o caminho do comando ex: /bin/ls onde ls é o comando
char	*ft_get_cmd_path(t_pipex *pipex, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (pipex->path[i])
	{
		temp = ft_strjoin(pipex->path[i], cmd);
		if (!access(temp, F_OK))
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

void	ft_child(char **envp, t_cmd *cmd, t_pipex *pipex, int flag)
{
	if (flag == 0)
	{
		if (dup2(pipex->infile_fd, STDIN_FILENO))
			exit(0);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->infile_fd);
		close(pipex->pipe_fd[0]);
	}
	else
	{
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO))
			exit(0);
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->infile_fd);
		close(pipex->pipe_fd[1]);
	}
	execve(cmd->path, cmd->args, envp);
}

//this function will get the array of the commands
void	ft_get_cmds(t_pipex *pipex, char **av)
{
	pipex->cmd1.args = ft_split(av[2], ' ');
	pipex->cmd2.args = ft_split(av[3], ' ');
	pipex->cmd1.path = ft_get_cmd_path(pipex, pipex->cmd1.args[0]);
	pipex->cmd2.path = ft_get_cmd_path(pipex, pipex->cmd2.args[0]);
}

void	ft_open_fds(t_pipex *pipex, char **av)
{
	pipex->infile_fd = open(av[1], O_RDONLY);
	if (pipex->infile_fd == -1)
		perror(av[1]);
	pipex->outfile_fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (pipe(pipex->pipe_fd) == -1)
		perror("pipe error");
}

int	main(int ac, char **av, char **envp)
{
	t_pipex		pipex;
	pid_t		process_id1;
	pid_t		process_id2;

	if (ac == 5)
	{
		ft_open_fds(&pipex, av);
		pipex.path = ft_get_env_path(envp);
		ft_get_cmds(&pipex, av);
		process_id1 = fork();
		if (process_id1 == 0)
			ft_child(envp, &pipex.cmd1, &pipex, 0);
		process_id2 = fork();
		if (process_id2 == 0)
			ft_child(envp, &pipex.cmd2, &pipex, 1);
		ft_close_all(&pipex);
	}
	return (0);
}
