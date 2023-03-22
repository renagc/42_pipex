/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:31:32 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/03/22 16:48:54 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_check_access(char *cmd, char **splitted)
{
	int		i;
	char	*temp;

	i = 0;
	while (splitted[i])
	{
		temp = ft_strjoin(splitted[i], cmd);
		if (!access(temp, F_OK))
			return (temp);
		i++;
	}
	exit(0);
}

void	ft_verify_path_cmds(char **av, char **envp, t_struct *pipex)
{
	char	**split;
	char	*temp_path;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	split = ft_split(envp[i] + 5, ':');
	i = -1;
	while (split[++i])
	{
		temp_path = ft_strjoin(split[i], "/");
		free(split[i]);
		split[i] = temp_path;
	}
	pipex->cmd1 = ft_split(av[2], ' ');
	pipex->cmd2 = ft_split(av[3], ' ');
	pipex->cmd1_path = ft_check_access(pipex->cmd1[0], split);
	pipex->cmd2_path = ft_check_access(pipex->cmd2[0], split);
}

void	child(t_struct *pipex, char **envp)
{
	//pipe_fd[0] read end from the pipe
	close(pipex->pipe_fd[0]);
	//write end - dup2 duplicate
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->pipe_fd[1]);
	execve(pipex->cmd1_path, pipex->cmd1, envp);
}

void	parent(t_struct *pipex, char **envp)
{
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	execve(pipex->cmd2_path, pipex->cmd2, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_struct	pipex;

	ft_basic_errors(ac, av, &pipex);
	ft_verify_path_cmds(av, envp, &pipex);
	if (pipe(pipex.pipe_fd) == -1)
		exit(0);
	pipex.pid = fork();
	if (pipex.pid == -1)
		exit(0);
	if (pipex.pid == 0) //child
		child(&pipex, envp);
	else //parent
		parent(&pipex, envp);
	ft_printf("ok por enquanto\n");
	return (0);
}
