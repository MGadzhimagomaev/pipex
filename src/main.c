/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:15:28 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/12/20 21:42:07 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_exit(int e, char *cmd, char *path, char **args)
{
	ft_putstr_fd("pipex: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (e == ENOENT)
		ft_putendl_fd(": command not found", 2);
	else if (e == EACCES)
		ft_putendl_fd(": permission denied", 2);
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(e), 2);
	}
	if (path)
		free(path);
	if (args)
		ft_free_tab(args);
	if (e == ENOENT)
		exit(127);
	if (e == EACCES)
		exit(126);
	exit(1);
}

static void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		exit(127);
	path = get_path(args[0], env);
	if (!path)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		ft_free_tab(args);
		exit(127);
	}
	execve(path, args, env);
	ft_exit(errno, args[0], path, args);
}

static void	exec_cmd1_process(char **argv, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(argv[1], 0);
	if (fd == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		exit(1);
	}
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(fd);
	close(p_fd[0]);
	close(p_fd[1]);
	exec(argv[2], env);
}

void	exec_cmd2_process(char **argv, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(argv[4], 1);
	if (fd == -1)
		exit(1);
	dup2(p_fd[0], 0);
	dup2(fd, 1);
	close(fd);
	close(p_fd[0]);
	close(p_fd[1]);
	exec(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		st1;
	int		st2;

	if (argc != 5)
		exit_handler();
	if (pipe(p_fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
		exec_cmd1_process(argv, p_fd, env);
	pid2 = fork();
	if (pid2 == 0)
		exec_cmd2_process(argv, p_fd, env);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, &st1, 0);
	waitpid(pid2, &st2, 0);
	if (WIFEXITED(st2))
		return (WEXITSTATUS(st2));
	if (WIFSIGNALED(st2))
		return (128 + WTERMSIG(st2));
	return (1);
}
