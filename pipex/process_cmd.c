/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:04 by ychng             #+#    #+#             */
/*   Updated: 2023/11/09 17:05:01 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static void	free_cmd_tokens(char **cmd_tokens)
{
	size_t	i;

	i = 0;
	while (cmd_tokens[i])
	{
		free(cmd_tokens[i]);
		i++;
	}
	free(cmd_tokens);
}

void	process_cmd(int argc, char **argv, char **envp)
{
	int		cmd_index;
	int		pipe_fd[2];
	char	**cmd_tokens;

	cmd_index = 1;
	setup_pipe_fd(pipe_fd);
	while (++cmd_index <= (argc - 2))
	{
		tokenize_cmd(argv[cmd_index], envp, &cmd_tokens);
		execute_cmd((t_execute_cmd){cmd_index, pipe_fd, argv, cmd_tokens});
		free_cmd_tokens(cmd_tokens);
	}
}
