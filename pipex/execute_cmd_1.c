/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:19:00 by ychng             #+#    #+#             */
/*   Updated: 2023/11/09 17:04:48 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static void	handle_first_cmd(t_execute_cmd params)
{
	char	*delim;
	int		file_fd;

	if (setup_file_fd(params.argv[1], &file_fd, params, true) == -1)
		return ;
	execute_first_cmd(file_fd, params.pipe_fd, params.cmd_tokens);
	close(file_fd);
}

static void	handle_last_cmd(t_execute_cmd params)
{
	int	file_fd;

	setup_file_fd(params.argv[params.cmd_index + 1], &file_fd, params, false);
	execute_last_cmd(file_fd, params.pipe_fd, params.cmd_tokens);
	close(file_fd);
}

static size_t	count_argv(char **argv)
{
	size_t	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

void	execute_cmd(t_execute_cmd params)
{
	size_t	first_cmd_index;

	first_cmd_index = 2;
	if (params.cmd_index == first_cmd_index)
		handle_first_cmd(params);
	else if (params.cmd_index == (count_argv(params.argv) - 2))
		handle_last_cmd(params);
	else
		execute_cmd_in_between(params.pipe_fd, params.cmd_tokens);
}
