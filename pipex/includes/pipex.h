/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:07:18 by ychng             #+#    #+#             */
/*   Updated: 2023/11/08 22:28:20 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "sys_headers.h"
# include "libft.h"
# include "get_next_line.h"

typedef struct s_execute_cmd
{
	int		cmd_index;
	int		*pipe_fd;
	char	**argv;
	char	**cmd_tokens;
}	t_execute_cmd;

// pipex.c
void	write_error(char *msg);
void	process_cmd(int argc, char **argv, char **envp);

// setup_functions.c
void	setup_pipe_fd(int *pipe_fd);
void	setup_here_doc(char *delim, int *pipe_fd);
int		setup_file_fd(char *file_path, int *file_fd,
			t_execute_cmd params, bool read_only);

// tokenize_cmd.c
void	tokenize_cmd(char *cmd, char **envp, char ***cmd_tokens);

// execute_cmd_1.c
void	execute_cmd(t_execute_cmd params);

// execute_cmd_2.c
void	execute_cmd_in_between(int *pipe_fd, char **cmd_tokens);
void	execute_last_cmd(int file_fd, int *pipe_fd, char **cmd_tokens);
void	execute_first_cmd(int file_fd, int *pipe_fd, char **cmd_tokens);

#endif