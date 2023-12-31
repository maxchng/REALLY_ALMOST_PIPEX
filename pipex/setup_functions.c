/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:14:44 by ychng             #+#    #+#             */
/*   Updated: 2023/11/09 17:05:05 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	setup_pipe_fd(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		write_error("pipe function didn't work\n");
		exit(-1);
	}
}

int	setup_file_fd(char *file_path, int *file_fd,
	t_execute_cmd params, bool read_only)
{
	int		mode;
	mode_t	permission;

	if (read_only == true)
	{
		*file_fd = open(file_path, O_RDONLY);
		if (*file_fd == -1)
		{
			write_error("stdin file doesn't exist\n");
			return (-1);
		}
	}
	else
	{
		permission = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
		mode = O_WRONLY | O_CREAT | O_TRUNC;
		*file_fd = open(file_path, mode, permission);
	}
	return (0);
}
