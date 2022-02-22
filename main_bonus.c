/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:23:39 by mmalphit          #+#    #+#             */
/*   Updated: 2022/02/22 16:24:23 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	**path;

	if (argc >= 5)
	{
		path = get_path(envp);
		pipex(argv, path, argc, envp);
	}
	else
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (1);
	}
	return (0);
}
