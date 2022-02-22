/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:23:41 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:26:21 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_here_doc_line(char **argv, t_fd t_fd)
{
	char	*line;
	size_t	limiter_length;

	line = get_next_line(0);
	if (!line)
		return (-1);
	limiter_length = ft_strlen(argv[2]);
	while (ft_strncmp(line, argv[2], limiter_length) != 0
		|| ft_strlen(line) != limiter_length + 1)
	{
		write(t_fd.fds[t_fd.i][1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
		if (!line)
			break ;
	}
	if (line)
		free(line);
	return (0);
}

static void	close_three(t_fd t_fd)
{
	close(t_fd.fds[t_fd.i][1]);
	close(t_fd.fds[t_fd.i][0]);
	close(t_fd.fds[t_fd.i + 1][1]);
}

int	here_doc_call(char **argv, char **path, t_fd t_fd, char **envp)
{
	int		pid;
	int		fd[2];

	pid = fork();
	if (pid < 0)
	{
		close_three(t_fd);
		return (-1);
	}
	if (pid == 0)
	{
		get_here_doc_line(argv, t_fd);
		fd[0] = dup(t_fd.fds[t_fd.i][0]);
		fd[1] = dup(t_fd.fds[t_fd.i + 1][1]);
		close_free_fds(t_fd, 1);
		if (fd[1] == -1 || fd[0] == -1)
			fatal_error_free(argv[3], path);
		cmd_process(argv[3], path, fd, envp);
	}
	close_three(t_fd);
	waitpid(pid, NULL, 0);
	return (0);
}
