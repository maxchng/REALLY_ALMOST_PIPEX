/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:17:14 by ychng             #+#    #+#             */
/*   Updated: 2023/11/09 17:06:12 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	check_exit_status(int status, char *cmd_name)
{
	if (WEXITSTATUS(status) != 0)
	{
		write_error(cmd_name);
		write_error(" command doesn't exist\n");
	}
}

void	execute_first_cmd(int file_fd, int *pipe_fd, char **cmd_tokens)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		write_error("fork function didn't work in execute_first_cmd\n");
		close(file_fd);
		exit(-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(file_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (execve(cmd_tokens[0], cmd_tokens, NULL) == -1)
			exit(-1);
	}
	waitpid(pid, &status, 0);
	check_exit_status(status, cmd_tokens[0]);
}

void	execute_last_cmd(int file_fd, int *pipe_fd, char **cmd_tokens)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		write_error("fork function didn't work in execute_last_cmd\n");
		close(file_fd);
		exit(-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		if (execve(cmd_tokens[0], cmd_tokens, NULL) == -1)
			exit(-1);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	check_exit_status(status, cmd_tokens[0]);
}

static void	copy_pipe_fd(int *pipe_fd, int *prev_pipe_fd)
{
	prev_pipe_fd[0] = pipe_fd[0];
	prev_pipe_fd[1] = pipe_fd[1];
}

void	execute_cmd_in_between(int *pipe_fd, char **cmd_tokens)
{
	int		prev_pipe_fd[2];
	pid_t	pid;
	int		status;

	copy_pipe_fd(pipe_fd, prev_pipe_fd);
	setup_pipe_fd(pipe_fd);
	pid = fork();
	if (pid < 0)
	{
		write_error("fork function didn't work in execute_cmd_in_between\n");
		exit(-1);
	}
	if (pid == 0)
	{
		close(prev_pipe_fd[1]);
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (execve(cmd_tokens[0], cmd_tokens, NULL) == -1)
			exit(-1);
	}
	close(prev_pipe_fd[0]);
	close(prev_pipe_fd[1]);
	waitpid(pid, &status, 0);
	check_exit_status(status, cmd_tokens[0]);
}
