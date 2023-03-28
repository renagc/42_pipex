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
		free(temp);
		i++;
	}
	return (NULL);
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
	free_array(split);
	if (!pipex->cmd1_path || !pipex->cmd2_path)
	{
		frees(pipex);
		exit (1);
	}
}

void	child1(t_struct *pipex, char **envp)
{
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	execve(pipex->cmd1_path, pipex->cmd1, envp);
}

void	child2(t_struct *pipex, char **envp)
{
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	execve(pipex->cmd2_path, pipex->cmd2, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_struct	pipex;

	ft_basic_errors(ac, av, &pipex);
	ft_verify_path_cmds(av, envp, &pipex);
	if (pipe(pipex.pipe_fd) == -1)
		exit(0);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		exit(0);
	if (pipex.pid1 == 0)
		child1(&pipex, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child2(&pipex, envp);
	frees(&pipex);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	close(pipex.infile);
	close(pipex.outfile);
	return (0);
}
