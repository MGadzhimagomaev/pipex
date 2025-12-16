/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:15:36 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/12/16 21:24:48 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_handler(void)
{
	ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit (1);
}

int	open_file(char *file, int is_out)
{
	int	output;

	if (!is_out)
		output = open(file, O_RDONLY);
	else
		output = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (output);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**p;
	char	*path;
	char	*full;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = ft_getenv("PATH", env);
	p = ft_split(path, ':');
	if (!path || !p)
		return (NULL);
	i = -1;
	while (p[++i])
	{
		path = ft_strjoin(p[i], "/");
		full = ft_strjoin(path, cmd);
		free(path);
		if (!full || access(full, X_OK) == 0)
			return (ft_free_tab(p), full);
		free (full);
	}
	ft_free_tab(p);
	return (NULL);
}
