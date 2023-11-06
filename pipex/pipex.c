/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:07:23 by ychng             #+#    #+#             */
/*   Updated: 2023/11/06 13:04:08 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	write_error(char *msg)
{
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		write_error("please write in the proper format:"
			" ./pipex file1 cmd1 cmd2 file2\n");
		exit(-1);
	}
	process_cmd(argc, argv, envp);
}
