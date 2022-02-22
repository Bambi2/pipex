/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:23:33 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:26:18 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_call(char **argv, char **path, t_fd *t_fd, char **envp)
{
	if (ft_strncmp("here_doc", argv[1], 8) == 0 && ft_strlen(argv[1]) == 8)
	{
		t_fd->is_here_doc = 1;
		if (here_doc_call(argv, path, *t_fd, envp) == -1)
			perror("fork");
		t_fd->i++;
		return (1);
	}
	else
	{
		t_fd->is_here_doc = 0;
		if (first_cmd_call(argv + 1, path, *t_fd, envp) == -1)
			perror("fork");
		return (2);
	}
}

void	pipex(char **argv, char **path, int argc, char **envp)
{
	int		i;
	t_fd	t_fd;

	i = 1;
	t_fd.i = 0;
	t_fd.fds = open_pipes(argc, argv);
	if (!t_fd.fds)
		fatal_error_free("pipe", path);
	if (first_call(argv, path, &t_fd, envp) == 1)
		i += 3;
	else
		i += 2;
	while (i < argc - 2)
	{
		if (cmd_call(argv[i], path, t_fd, envp) == -1)
			perror("fork");
		i++;
		t_fd.i++;
	}
	if (last_cmd_call(argv + i, path, t_fd, envp) == -1)
		perror("fork");
	free_two_dim(path);
	free_two_dim_int(t_fd.fds);
}
