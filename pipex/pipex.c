/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:07:23 by ychng             #+#    #+#             */
/*   Updated: 2023/11/04 19:03:18 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	exit_program(char *msg)
{
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		exit_program("please write in the proper format:"
			" ./pipex file1 cmd1 cmd2 file2.\n");
	}
	process_cmd(argc, argv, envp);
}
